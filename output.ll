@z global float 0
@y global i32 0
@x global i32 0

define i32 @plus(i32 %b_t, i32 %a_t) {
entry:

%b = alloca i32
store i32 %b_t, ptr %b
%a = alloca i32
store i32 %a_t, ptr %a
%z = alloca float
%y = alloca i32
%x = alloca i32
