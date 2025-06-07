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
%0 = load i32, ptr %x
%1 = add i32 0, 10
%2 = add i32 0, 5
%3 = add i32 %1, %2
%4 = mul i32 %0, %3
store i32 %4, ptr  %tes
%5 = add i32 0, 5
store i32 %5, ptr  %y
%6 = load i32, ptr %tes
%7 = load i32, ptr %y
%8 = add i32 %6, %7
store i32 %8, ptr  %tes
