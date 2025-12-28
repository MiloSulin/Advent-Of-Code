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

    var threaded = std.Io.Threaded.init(std.heap.smp_allocator);
    const io = threaded.ioBasic();

    var input_buffer: [10*5120]u8 = undefined;
    var input_reader: std.fs.File.Reader = input_file.reader(io, &input_buffer);
    const input_interface = &input_reader.interface;

    var safe_pos: i32 = 50;
    var zero_count: u32 = 0;
    var zero_count2: u32 = 0;

    // solve tasks
    while (input_interface.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("Current pos: {d}\n", .{safe_pos});
            var action: i32 = try std.fmt.parseInt(i32, value[1..], 10);
            if (value[0] == 'L') action = -action;
            var extra_clicks: u32 = @divFloor(@abs(action), 100);
            action = @rem(action, 100);
            const new_value: i32 = safe_pos + action;
            if (new_value == 0) {
                extra_clicks += 1;
            } else if (safe_pos != 0) {
                extra_clicks += @abs(@divFloor(new_value, 100));
            }
            safe_pos = @mod(new_value, 100);
            if (safe_pos == 0) zero_count += 1;
            zero_count2 += extra_clicks;
        } else break;
    } else |err| switch (err) {
        error.ReadFailed,
        error.StreamTooLong,
        => |e| return e,
        else => unreachable,
    }
    try stdout.print("Solution to task 1: {}.\n", .{zero_count});
    try stdout.print("Solution to task 2: {}.\n", .{zero_count2});

    const run_time: u64 = timer.read();
    try stdout.print("Execution time was: {d:.3} ns.\n", .{run_time});
    try stdout.flush();
}
