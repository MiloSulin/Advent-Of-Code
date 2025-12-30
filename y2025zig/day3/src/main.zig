const std = @import("std");

pub fn main() !void {
    // start timer
    var timer = try std.time.Timer.start();

    var stdout_buffer: [1024]u8 = undefined;
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    // read input
    const cwd = std.fs.cwd();
    const input_file = try cwd.openFile("input.txt", .{});
    defer input_file.close();

    var input_buffer: [5120*5]u8 = undefined;
    var threaded = std.Io.Threaded.init(std.mem.Allocator.failing);
    defer threaded.deinit();
    const io = threaded.ioBasic();

    var reader: std.fs.File.Reader = input_file.reader(io, &input_buffer);
    const input_reader = &reader.interface;

    // solve tasks
    var solution1: u64 = 0;
    var solution2: u64 = 0;
    var numbers: [100]u8 = .{0} ** 100;
    var indices: [12]usize = .{0} ** 12;
    // var test_n: u8 = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            for (value, 0..value.len) |num, i| {
                numbers[i] = try std.fmt.charToDigit(num, 10);
            }
            indices = getLargestIndices(&numbers);
            const digit1_i: usize = std.mem.findMax(u8, numbers[0..99]);
            const digit2_i: usize = std.mem.findMax(u8, numbers[digit1_i+1..]) + digit1_i+1;
            solution1 += 10*numbers[digit1_i] + numbers[digit2_i];
            solution2 += try getNumber(&indices, &numbers);
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

pub fn getLargestIndices(slice: []u8) [12]usize {
    var indices: [12]usize = undefined;
    var i: u8 = 11;
    indices[0] = std.mem.findMax(u8, slice[0..slice.len-11]);
    var previous: usize = indices[0];
    while (i > 1) : (i -= 1) {
        indices[12-i] = std.mem.findMax(u8, slice[previous+1..slice.len-i+1]) + previous+1;
        previous = indices[12-i];
    }
    indices[11] = std.mem.findMax(u8, slice[previous+1..]) + previous+1;
    return indices;
}

pub fn getNumber(indices: []usize, numbers: []u8) !u64 {
    var result: u64 = 0;
    for (indices, 1..13) |i, j| {
        const num = numbers[i];
        result += try std.math.powi(u64, 10, 12-j) * num;
    }
    return result;
}
