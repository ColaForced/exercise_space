# calc: add.o div.o sub.o mult.o main.o
# 	gcc add.o div.o sub.o mult.o main.o -o calc

# CFLAGS = -O3
# target = calc
# obj = add.o div.o sub.o mult.o main.o

# $(target):$(obj)
# 	gcc $(obj) -o $(target)



# 这是一个规则，里边使用了自定义变量
# 使用自动变量, 替换相关的内容
calc:add.o																																																																																																										div.o  main.o  mult.o  sub.o
	gcc $^ -o $@ 			# 自动变量只能在规则的命令中使用

