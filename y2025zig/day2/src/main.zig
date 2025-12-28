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

    var input_buffer: [5120]u8 = undefined;
    var threaded = std.Io.Threaded.init(std.mem.Allocator.failing);
    defer threaded.deinit();
    const io = threaded.ioBasic();

    var reader: std.fs.File.Reader = input_file.reader(io, &input_buffer);
    const input_reader = &reader.interface;

    // solve tasks
    var solution1: u64 = 0;
    var solution2: u64 = 0;
    const primes = [_]u64{2, 3, 5, 7};
    // std.debug.print("test: {}\n", .{2 % 3});

    while (input_reader.takeDelimiter(',')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            var tokens = std.mem.tokenizeAny(u8, value, "-\n");
            const start: u64 = try std.fmt.parseInt(u64, tokens.next().?, 10);
            const end: u64 = try std.fmt.parseInt(u64, tokens.next().?, 10);

            for (start..end+1) |i| {
                const current: u64 = @intCast(i);
                const log_n: f64 = @log10(@floatFromInt(current));
                const order: u64 = @intFromFloat(@floor(log_n));
                // std.debug.print("number: {}\n", .{current});

                for (primes) |prime| {
                    // std.debug.print("prime: {}\n", .{prime});
                    if ( @mod(order+1, prime) == 0) {
                        const denominator: u64 = try getDenom(order, prime);
                        // std.debug.print("denom: {}\n", .{denominator});
                        if (current % denominator == 0) {
                            solution2 += current;
                            if (prime == 2) solution1 += current;
                            break;
                        }
                    }
                }
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

    const run_time: u64 = timer.read();
    try stdout.print("Execution time was: {d:.3} ns.\n", .{run_time});
    try stdout.flush();
}

pub fn getDenom(order: u64, prime: u64) !u64 {
    const step: u64 = (order+1) / prime;
    var denom: u64 = 0;
    var i: i128 = order+1-step;
    while (i >= 0) : (i -= step) {
        denom += try std.math.powi(u64, 10, @intCast(i));
    }
    return denom;
}
