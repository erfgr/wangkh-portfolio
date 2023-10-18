# PA1 Pre-release Version

### Why pre-release?

Because the OJ is not available now. However, it's a good choice to start programming early and make full use of the holiday. You can read the problem statements, write programs, and preliminary test the correctness locally.



### Pre-reading

[欢迎走进ShanghaiTech CS101](https://mp.weixin.qq.com/s/Ab0mSdIcHBMcivHXzGYNsg) 编程作业小节

[如何编程完成一道算法题](https://mp.weixin.qq.com/s/tXRor1wRlRFZMSbRoVFV_w)



### Note for the Problems

There are 4 problems in PA1:

- Template: An interactive problem. For some technical issues, Template is not released here temporarily. You cannot use any STL algorithm or container.
- A, B, C: All of them traditional problems. You can use STL algorithms and containers.



### Note for the Constraints and Time Limit

For each problem, we provide several levels of constraints. If your algorithm is not general, or has a high time complexity, you will not pass those testcases with looser constraints.

There is a time limit for each testcase, usually between $1$s and $10$s. Since a common computer can perform $10^8\sim10^9$ basic operations per second, you can estimate the running time of your algorithm by analyzing its time complexity.



### Note for the Input and Output Efficiency

Since the input scale is very large for some testcases, you may need to utilize some better optimization. You could get more information in the WeChat post *如何编程完成一道算法题——特别篇：关于输入*.

We provide an example (in C++) for you:

```cpp
void read(int &x)
{
    auto c=getchar();x=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);x=(x<<1)+(x<<3)+(c^'0'),c=getchar());
}
```

You can use `read(x)` to read a variable `x`.

