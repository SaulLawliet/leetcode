# [LeetCode OJ](https://leetcode.com/)

- 为了巩固 C 语言, 所以暂时只用 C 解题
- 每个 solution 都包含单元测试
- 最后, 特别感谢 [miloyip/json-tutorial](https://github.com/miloyip/json-tutorial)

## 脚本使用说明

``` sh
# 执行第1题
c/test.sh 1
# 执行前10题
c/test.sh $(seq 10)
# 执行全部题
c/test.sh all
# 执行库文件的测试
c/test.sh lib

# -m 开启内存泄露检查, 使用valgrind, 如
c/test.sh -m 1
c/test.sh -m all
c/test.sh -m lib
```

## 其他

官方会调整函数的参数以及测试用例  
如果有小伙伴发现失效的解答  
可以提醒我一下, 多谢~❤️
