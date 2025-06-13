declare i32 @printf(ptr noundef, ...)
declare i32 @__isoc99_scanf(ptr noundef, ...)
@read_int = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@write_int = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@read_float = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@write_float = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

@b global i32 0
@a global i32 0


define i32 @main(){
entry:
%0 = add i32 0, 10
store i32 %0, ptr @a
br label %while_1

while_1:
%1 = add i32 0, 0
%2 = load i32, ptr @a
%3 = icmp sgt %2, %1
br i1 %3, label %do_1, label %end_while_1

do_1:
%4 = load i32, ptr @a
%5 = call i32 (ptr, ...) @printf(ptr @write_int, i32 %4)
%6 = add i32 0, 1
%7 = load i32, ptr @a
%8 = sub i32 %7, %6
store i32 %8, ptr @a
%9 = add i32 0, 5
store i32 %9, ptr @b
br label %while_2

while_2:
%10 = add i32 0, 0
%11 = load i32, ptr @b
%12 = icmp sgt %11, %10
br i1 %12, label %do_2, label %end_while_2

do_2:
%13 = load i32, ptr @b
%14 = call i32 (ptr, ...) @printf(ptr @write_int, i32 %13)
%15 = add i32 0, 1
%16 = load i32, ptr @b
%17 = sub i32 %16, %15
store i32 %17, ptr @b
br label %while_2

end_while_2:
br label %while_1

end_while_1:
ret i32 0
}