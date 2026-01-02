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
    var solution1: usize = 0;
    var solution2: usize = 0;
    var state: [141]usize = .{0} ** 141;
    // var test_n: u8 = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            var new_state: [141]usize = .{0} ** 141;
            for (value, 0..value.len) |c, i| {
                switch (c) {
                    'S' => new_state[i] = 1,
                    '.' => new_state[i] += state[i],
                    '^' => {
                        if (state[i] >= 1) {
                            new_state[i-1] += state[i];
                            new_state[i+1] += state[i];
                            solution1 += 1;
                        }
                        new_state[i] = 0;
                    },
                    else => unreachable,
                }
            }
            state = new_state;
        } else break;
    } else |err| switch (err) {
        error.ReadFailed,
        error.StreamTooLong,
        => |e| return e,
        else => unreachable,
    }
    const result_v: @Vector(141, usize) = state;
    solution2 += @reduce(.Add, result_v);

    // print solutions
    try stdout.print("Solution to task 1: {}.\n", .{solution1});
    try stdout.print("Solution to task 2: {}.\n", .{solution2});

    const run_time: f64 = @floatFromInt(timer.read());
    try stdout.print("Execution time was: {d:.3} ms.\n", .{run_time / 1_000_000});
    try stdout.flush();
}
