@z global i32 0
@y global i32 0
@x global i32 0

define i32 @plus(i32 %a_t, i32 %b_t, ptr %c) {
entry:

%a = alloca i32
store i32 %a_t, ptr %a
%b = alloca i32
store i32 %b_t, ptr %b
%plus = alloca i32
%0 = load i32, ptr %a
%1 = load i32, ptr %b
%2 = add i32 %0, %1
store i32 %2, ptr %plus
%3 = load i32, ptr %plus
ret i32 %3
}

define i32 @main(){
entry:
%4 = load i32, ptr @x
%5 = load i32, ptr @y
%6 = call i32 @plus(i32 %4, i32 %5, ptr @z)
store i32 %6, ptr @z
ret i32 0
}