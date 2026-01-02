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
    const n = 499_500;
    var vertices: Vertices = .{
        .component = .{0} ** 1024,
        .x = undefined,
        .y = undefined,
        .z = undefined,
    };
    var edges: Edges = .{
        .len = n,
        .pos = 0,
        .edges = undefined,
    };
    var components: Components = .{ .elements = .{0} ** 512 };
    var vertex_n: usize = 0;
    // var test_n: u8 = 0;

    while (input_reader.takeDelimiter('\n')) |line| {
        if (line) |value| {
            // std.debug.print("This was read: {s}\n", .{value});
            var iterator = std.mem.tokenizeScalar(u8, value, ',');
            vertices.x[vertex_n] = try std.fmt.parseInt(usize, iterator.next().?, 10);
            vertices.y[vertex_n] = try std.fmt.parseInt(usize, iterator.next().?, 10);
            vertices.z[vertex_n] = try std.fmt.parseInt(usize, iterator.next().?, 10);
            vertex_n += 1;
        } else break;
    } else |err| switch (err) {
        error.ReadFailed,
        error.StreamTooLong,
        => |e| return e,
        else => unreachable,
    }

    var edge_count: usize = 0;
    for (0..vertex_n) |i| {
        for (i+1..vertex_n) |j| {
            // edges.v1[edge_count] = i;
            // edges.v2[edge_count] = j;
            // edges.dist[edge_count] = vertices.distance(i, j);
            edges.edges[edge_count] = Edge{.v1 = i, .v2 = j, .dist = vertices.distance(i, j)};
            edge_count += 1;
        }
    }

    edges.sort();

    var keep_going: usize = 1;
    var com_sizes: [512]u16 = undefined;
    while (keep_going > 0) {
        const shortest: [2]usize = edges.getShortest();
        vertices.connect(&components, shortest[0], shortest[1]);
        if (keep_going == 1001) {
            com_sizes = components.elements;
            std.mem.sortUnstable(u16, &com_sizes, {}, lessThan);
            const three_biggest: @Vector(3, u16) = com_sizes[0..3].*;
            solution1 += @reduce(.Mul, three_biggest);
        }
        if (components.elements[vertices.component[0]-1] == vertex_n) {
            solution2 += vertices.x[shortest[0]] * vertices.x[shortest[1]];
            break;
        }
        keep_going += 1;
    }

    // print solutions
    try stdout.print("Solution to task 1: {}.\n", .{solution1});
    try stdout.print("Solution to task 2: {}.\n", .{solution2});

    const run_time: f64 = @floatFromInt(timer.read());
    try stdout.print("Execution time was: {d:.3} ms.\n", .{run_time / 1_000_000});
    try stdout.flush();
}

const Vertices = struct {
    component: [1024]usize,
    x: [1024]usize,
    y: [1024]usize,
    z: [1024]usize,

    pub fn distance(self: *Vertices, a: usize, b: usize) f64 {
        const point1: @Vector(3, f64) = @floatFromInt(@Vector(3, u64){self.x[a], self.y[a], self.z[a]});
        const point2: @Vector(3, f64) = @floatFromInt(@Vector(3, u64){self.x[b], self.y[b], self.z[b]});
        const dist: @Vector(3, f64) = (point1 - point2) * (point1 - point2);
        const result: f64 = @sqrt(@reduce(.Add, dist));
        return result;
    }

    pub fn connect(self: *Vertices, comps: *Components, a: usize, b:usize) void {
        const com1: usize = self.component[a];
        const com2: usize = self.component[b];
        if (com1 != com2) {
            if (com1 == 0) {
                comps.addTo(com2-1);
                self.component[a] = com2;
            } else if (com2 == 0) {
                comps.addTo(com1-1);
                self.component[b] = com1;
            } else {
                comps.combine(com1-1, com2-1);
                std.mem.replaceScalar(usize, &self.component, com2, com1);
            }
        } else if (com1 == 0) {
            const new_com = comps.add()+1;
            self.component[a] = new_com;
            self.component[b] = new_com;
        }
    }
};

const Edge = struct {
    v1: usize,
    v2: usize,
    dist: f64,
};

const Edges = struct {
    len: usize,
    pos: usize,
    edges: [512*1024]Edge,

    fn lessThan(_: void, lhs: Edge, rhs: Edge) bool {
        if (lhs.dist < rhs.dist) return true;
        return false;
    }

    pub fn sort(self: *Edges) void {
        std.mem.sortUnstable(Edge, self.edges[0..self.len], {}, Edges.lessThan);
    }

    pub fn getShortest(self: *Edges)  [2]usize {
        const result: [2]usize = .{self.edges[self.pos].v1, self.edges[self.pos].v2};
        self.pos += 1;
        return result;
    }
};

// const Edges = struct {
//     len: usize,
//     v1: [512*1024]usize,
//     v2: [512*1024]usize,
//     dist: [512*1024]f64,
//
//     pub fn getShortest(self: *Edges) [2]usize {
//         var result: [2]usize = undefined;
//         const shortest = std.mem.findMin(f64, self.dist[0..self.len]);
//         // std.debug.print("{d}\n", .{self.dist[shortest]});
//         result[0] = self.v1[shortest];
//         result[1] = self.v2[shortest];
//         std.mem.swap(usize, &self.v1[shortest], &self.v1[self.len-1]);
//         std.mem.swap(usize, &self.v2[shortest], &self.v2[self.len-1]);
//         std.mem.swap(f64, &self.dist[shortest], &self.dist[self.len-1]);
//         self.len -= 1;
//         return result;
//     }
// };

const Components = struct {
    elements: [512]u16,

    pub fn combine(self: *Components, a: usize, b: usize) void {
        self.elements[a] += self.elements[b];
        self.elements[b] = 0;
    }

    pub fn add(self: *Components) usize {
        for (self.elements[0..], 0..self.elements.len) |a, i| {
            if (a == 0) {
                self.elements[i] = 2;
                return i;
            }
        }
        return 0;
    }

    pub fn addTo(self: *Components, a: usize) void {
        self.elements[a] += 1;
    }
};

pub fn lessThan(_: void, lhs: u16, rhs: u16) bool {
    if (lhs > rhs) {
        return true;
    }
    return false;
}
