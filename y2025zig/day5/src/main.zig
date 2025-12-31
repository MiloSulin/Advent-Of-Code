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
    var or_range: OrRange = OrRange{
        .start_i = .{0} ** 1024,
        .end_i = .{0} ** 1024,
        .len = 0,
    };
    var mode: u8 = 1;
    // var test_n: u8 = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            if (value.len == 0) {
                mode = 2;
                continue;
            }
            switch (mode) {
                1 => {
                    var iterator = std.mem.tokenizeScalar(u8, value, '-');
                    const start: usize = try std.fmt.parseInt(usize, iterator.next().?, 10);
                    const end: usize = try std.fmt.parseInt(usize, iterator.next().?, 10);
                    or_range.addRange(start, end);
                },
                2 => {
                    const number: usize = try std.fmt.parseInt(usize, value, 10);
                    const in_range: ?usize = or_range.findRange(number);
                    if (in_range) |_| {
                        solution1 += 1;
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
    solution2 += or_range.numbersInRange();

    // print solutions
    try stdout.print("Solution to task 1: {}.\n", .{solution1});
    try stdout.print("Solution to task 2: {}.\n", .{solution2});

    const run_time: f64 = @floatFromInt(timer.read());
    try stdout.print("Execution time was: {d:.3} ms.\n", .{run_time / 1_000_000});
    try stdout.flush();
}

const OrRange = struct {
    start_i: [1024]usize,
    end_i: [1024]usize,
    len: usize,

    pub fn findRange(self: *OrRange, value: usize) ?usize {
        for (0..self.len) |i| {
            if (value >= self.start_i[i] and value <= self.end_i[i]) {
                return i;
            }
        }
        return null;
    }

    pub fn compareRange(lhs: usize, rhs: usize) std.math.Order {
        const result = std.math.order(lhs, rhs).invert();
        return result;
    }
    pub fn compareRange2(_: void, lhs: usize, rhs: usize) bool {
        if (lhs > rhs) {
            return true;
        }
        return false;
    }

    fn removeRange(self: *OrRange, value: usize) void {
        self.start_i[value] = 0;
        self.end_i[value] = 0;
    }

    fn sortRange(self: *OrRange) void {
        std.mem.sortUnstable(usize, self.start_i[0..self.len], {}, OrRange.compareRange2);
        std.mem.sortUnstable(usize, self.end_i[0..self.len], {}, OrRange.compareRange2);
    }

    fn addRange(self: *OrRange, start: usize, end: usize) void {
        const s_range: ?usize = self.findRange(start);
        const e_range: ?usize = self.findRange(end);
        var removed: usize = 0;

        if (s_range) |s_rvalue| {
            if (e_range) |e_rvalue| {
                if (s_rvalue != e_rvalue) {
                    self.end_i[s_rvalue] = self.end_i[e_rvalue];
                    for (e_rvalue..s_rvalue) |i| {
                        self.removeRange(i);
                        removed += 1;
                    }
                }
            } else {
                // find upper bound for end of range
                const e_ub: usize = std.sort.upperBound(usize, self.end_i[0..self.len], end, OrRange.compareRange);
                for (e_ub..s_rvalue) |i| {
                    self.removeRange(i);
                    removed += 1;
                }
                self.end_i[s_rvalue] = end;
            }
        } else if (e_range) |e_rvalue| {
            // find upper bound for start of range
            const s_ub: usize = std.sort.upperBound(usize, self.end_i[0..self.len], start, OrRange.compareRange);
            for (e_rvalue+1..s_ub) |i| {
                self.removeRange(i);
                removed += 1;
            }
            self.start_i[e_rvalue] = start;
        } else {
            // find upper bounds
            const s_ub: usize = std.sort.upperBound(usize, self.end_i[0..self.len], start, OrRange.compareRange);
            const e_ub: usize = std.sort.upperBound(usize, self.end_i[0..self.len], end, OrRange.compareRange);
            for (e_ub..s_ub) |i| {
                self.removeRange(i);
                removed += 1;
            }
            self.start_i[self.len] = start;
            self.end_i[self.len] = end;
            self.len += 1;
        }
        self.sortRange();
        self.len -= removed;
    }

    pub fn numbersInRange(self: *OrRange) usize {
        var result: usize = 0;
        for (0..self.len) |i| {
            result += self.end_i[i] - self.start_i[i] + 1;
        }
        return result;
    }
};
