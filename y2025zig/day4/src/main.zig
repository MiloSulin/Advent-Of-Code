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
    var grid_array: [135*137]u8 = .{0} ** (135*137);
    var row_n: u64 = 1;
    var indices: [8]usize = undefined;
    var to_remove: [1024*2]usize = undefined;
    var solution1_b: bool = true;
    // var test_n: u8 = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            for (value, 0..value.len) |num, i| {
                const offset: usize = row_n*135;
                grid_array[i+offset] = gridToNum(num);
            }
            row_n += 1;
        } else break;
    } else |err| switch (err) {
        error.ReadFailed,
        error.StreamTooLong,
        => |e| return e,
        else => unreachable,
    }

    var current: usize = 1;
    while (current != 0) {
        current = 0;
        for (135..(135*135)+135) |i| {
            const val: u8 = grid_array[i];
            if (val == 1) {
                var neighbours: u8 = 0;
                const indices1: []usize = getNeighbourIndices(i, &indices);
                for (indices1) |j| {
                    neighbours += grid_array[j];
                }
                switch (neighbours) {
                    0...3 => {
                        solution2 += 1;
                        to_remove[current] = i;
                        current += 1;
                    },
                    4...8 => {},
                    else => unreachable,
                }
            }
        }
        if (solution1_b) {
            solution1 = solution2;
            solution1_b = false;
        }
        for (to_remove[0..current]) |i| {
            grid_array[i] = 0;
        }
    }

    // print solutions
    try stdout.print("Solution to task 1: {}.\n", .{solution1});
    try stdout.print("Solution to task 2: {}.\n", .{solution2});

    const run_time: f64 = @floatFromInt(timer.read());
    try stdout.print("Execution time was: {d:.3} ms.\n", .{run_time / 1_000_000});
    try stdout.flush();
}

pub fn gridToNum(char: u8) u8 {
    switch (char) {
        '.' => return 0,
        '@' => return 1,
        else => unreachable,
    }
}

pub fn getNeighbourIndices(index: u64, indices: *[8]usize) []usize {
    var preceding: @Vector(8, usize) = undefined;
    var following: @Vector(8, usize) = undefined;
    var result: @Vector(8, usize) = undefined;
    switch (@mod(index, 135)) {
        0 => {
            preceding = .{135, 134, 0, 0, 0, 0, 0, 0};
            following = .{0, 0, 1, 135, 136, 0, 0, 0};
            result = .{index, index, index, index, index, 0, 0, 0};
            indices.* = (result - preceding) + following;
            return indices[0..5];
        },
        134 => {
            preceding = .{136, 135, 1, 0, 0, 0, 0, 0};
            following = .{0, 0, 0, 134, 135, 0, 0, 0};
            result = .{index, index, index, index, index, 0, 0, 0};
            indices.* = (result - preceding) + following;
            return indices[0..5];
        },
        else => {
            preceding = .{136, 135, 134, 1, 0, 0, 0, 0};
            following = .{0, 0, 0, 0, 1, 134, 135, 136};
            result = @splat(index);
            indices.* = (result - preceding) + following;
            return indices;
        }
    }
}
