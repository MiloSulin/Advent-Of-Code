const std = @import("std");

pub fn main() !void {
    // start timer
    var timer = try std.time.Timer.start();

    var stdout_buffer: [1024]u8 = undefined;
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    // read input into buffer
    const cwd = std.fs.cwd();
    const input_file = try cwd.openFile("input.txt", .{});
    defer input_file.close();

    var input_buffer: [5120*4]u8 = undefined;
    var threaded = std.Io.Threaded.init(std.mem.Allocator.failing);
    defer threaded.deinit();
    const io = threaded.ioBasic();

    var reader: std.fs.File.Reader = input_file.reader(io, &input_buffer);
    const input_reader = &reader.interface;

    // solve tasks
    var solution1: u64 = 0;
    var solution2: u64 = 0;
    var numbers: [4*1024]usize = undefined;
    var positions: [4*1048]usize = undefined;
    var row_n: u8 = 0;
    // var test_n: usize = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            switch (row_n) {
                0...3 => {
                    var place: usize = row_n;
                    var line_read: std.Io.Reader = .fixed(value);
                    while (line_read.takeDelimiterExclusive(' ')) |number| {
                        if (number.len != 0) {
                            const num: usize = try std.fmt.parseInt(usize, number, 10);
                            numbers[place] = num;
                            positions[place] = line_read.seek;
                            place += 4;
                        } else line_read.seek += 1;
                    } else |err| switch (err) {
                        error.ReadFailed,
                        error.StreamTooLong,
                        => |e| return e,
                        error.EndOfStream => {},
                        else => unreachable,
                    }
                    row_n += 1;
                },
                4 => {
                    var iterator = std.mem.tokenizeScalar(u8, value, ' ');
                    var place: usize = 0;
                    var num_buf: [4]u8 = undefined;
                    const one_vec: @Vector(4, usize) = .{1, 1, 1, 1};
                    while (iterator.next()) |op| {
                        var vec2: [4]usize = .{0, 0, 0, 0};
                        const numbers_s = numbers[place..place+4];
                        const vec: @Vector(4, usize) = numbers_s[0..4].*;
                        const vec_f: @Vector(4, f64) = @floatFromInt(vec);
                        const vec_log: @Vector(4, u8) = @intFromFloat(@floor(@log10(vec_f)));
                        const vec_len: [4]u8 = vec_log + @Vector(4, u8){1, 1, 1, 1};
                        const max_len = std.mem.max(u8, &vec_len);
                        const position_s = positions[place..place+4];
                        const all_eql = std.mem.allEqual(usize, position_s, position_s[0]);
                        for (numbers_s, 0..4) |num, i| {
                            const num_as_str = try std.fmt.bufPrint(&num_buf, "{}", .{num});
                            var ofst: u8 = 0;
                            if (all_eql) {
                                ofst += max_len - vec_len[i];
                            }
                            for (num_as_str, 0..num_as_str.len) |nc, j| {
                                const n = try std.fmt.charToDigit(nc, 10);
                                vec2[ofst+j] = vec2[ofst+j]*10 + n;
                            }
                        }
                        switch (op[0]) {
                            '+' => {
                                const vec3: @Vector(4, usize) = vec2;
                                solution1 += @reduce(.Add, vec);
                                solution2 += @reduce(.Add, vec3);
                            },
                            '*' => {
                                var vec3: @Vector(4, usize) = vec2;
                                const where_zero: @Vector(4, bool) = vec3 == @Vector(4, usize){0, 0, 0, 0};
                                vec3 = @select(usize, where_zero, one_vec, vec2);
                                solution1 += @reduce(.Mul, vec);
                                solution2 += @reduce(.Mul, vec3);
                            },
                            else => unreachable,
                        }
                        place += 4;
                    }
                },
                else => unreachable,
            }
        } else break;
    } else |err| switch (err) {
        error.ReadFailed,
        error.StreamTooLong,
        => |e| return e,
        else => unreachable,
    }

    // print solutions
    try stdout.print("Solution to task 1: {}.\n", .{solution1});
    try stdout.print("Solution to task 2: {}.\n", .{solution2});

    const run_time: f64 = @floatFromInt(timer.read());
    try stdout.print("Execution time was: {d:.3} ms.\n", .{run_time / 1_000_000});
    try stdout.flush();
}
