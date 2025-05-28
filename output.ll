@z global float 0
@y global i32 0
@x global i32 0

define i32 @plus(i32 %a_t, i32 %b_t) {
entry:

%a = alloca i32
store i32 %a_t, ptr %a
%b = alloca i32
store i32 %b_t, ptr %b
%tes = alloca i32
%t0 = add i32 0, 10
store i32 t0, ptr %tes
