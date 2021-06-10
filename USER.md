# 用户文档

## 类定义

### `Vector`模板类

非常简化的向量模板类。目前支持线性运算，功能类似`numpy`中的`array`，与`std::vector`不同。模板定义和拷贝控制成员类似`std::array`。
`Vector`模板类定义在头文件`Vector.h`中。

#### 声明

    template<class T, size_t n> struct Vector;

#### 拷贝控制

    (implicitly declared default/list/copy/move constructor)
    (implicitly declared copy/move assignment operator)
    (implicitly declared destructor)

同`std::array`，使用聚合类(`aggregate`)隐式定义的拷贝控制成员，需要注意默认初始化问题。

在`C++11`及以后标准下支持列表初始化。

#### 数据成员

    T data[n];

公开数据成员，可以直接访问。

#### 成员访问

    T &operator[](size_t i);
    const T &operator[](size_t i) const;

仅支持下标运算符，与公开数据成员data的下标运算等价。

#### 复合赋值运算（成员函数）

    Vector &operator+=(const Vector &);
    Vector &operator-=(const Vector &);
    Vector &operator*=(T);
    Vector &operator/=(T);

向量的加法和数乘运算，运算结果直接赋值到第一个操作数上，退回第一个操作数的引用。

#### 线性运算（非成员函数）

    template<class T, size_t n>
    Vector<T, n> operator+(Vector<T, n>, const Vector<T, n> &);

    template<class T, size_t n>
    Vector<T, n> operator-(Vector<T, n>, const Vector<T, n> &);

    template<class T, size_t n>
    Vector<T, n> operator*(Vector<T, n>, T);
    template<class T, size_t n>
    Vector<T, n> operator*(T, Vector<T, n>);

    template<class T, size_t n>
    Vector<T, n> operator/(Vector<T, n>, T);

线性运算的类外函数版本，退回运算结果而不改变操作数。

#### 输入输出

    template<class T, size_t n>
    std::istream &operator>>(std::istream &, Vector<T, n> &);
    template<class T, size_t n>
    std::istream &operator<<(std::istream &, Vector<T, n> &);

输入输出运算底层调用数据类型`T`定义的输入输出运算符，流状态的改变由后者决定。调用者有义务检查流状态的有效性。

### `Particle_Base`类

粒子的基类，定义在头文件`Particle.h`中。

#### 拷贝控制

    (implicitly declared default/list/copy/move constructor)
    (implicitly declared copy/move assignment operator)
    virtual ~Particle_Base();

除留空的虚析构函数外，使用聚合类的合成拷贝控制成员。

#### 数据成员

    size_t no;

粒子的编号。对于`pythia8`的日志文件而言，粒子的编号从`0`（`system`）开始，顺序排列。

    int id;

粒子的身份码。由`pythia8`定义。不同种类的粒子对应不同的身份码。

    std::string name;

粒子的名称。不同种类的粒子对应不同的名称。已消灭的粒子名称外包围一对圆括号。

    int status;

粒子的状态值。由`pythia8`定义。已消灭的粒子状态值为负数。

    size_t mothers[2];

从日志文件取得的粒子`mothers`信息，有固定长度`2`。可能含有重复或缺失，也可能含有无意义的`0`。

    size_t daughters[2];

从日志文件获得的粒子`daughter`信息，有固定长度`2`。同样该信息不是完善的。

    short colours[2];

粒子的色荷信息。将原始数据（三位阿拉伯数字）读如时可能出现进制问题，有待进一步改进。目前未使用该信息。（注意以`0`开头的数字可能被认为是八进制）

    Vector<double, 3> p;

粒子的动量信息，存储为直角坐标系下的三个分量。其单位一般为GeV/c。

    double e;

粒子的能量信息。其单位一般为GeV。

    double m;

粒子的静质量信息。其单位一般为GeV/c^2。

#### 成员函数

    Vector<double, 3> getv() const { return p / e; }

根据狭义相对论关系有：

<img src="http://latex.codecogs.com/gif.latex?
    \vec p = \frac{m\vec v}{\sqrt{1 - (v / c)^2}},\ 
    E = \frac{mc^2}{\sqrt{1 - (v / c)^2}}
"/>

则：

<img src="http://latex.codecogs.com/gif.latex?
    \vec v / c = \frac{\vec p / ({\rm GeV}/c)}{E / {\rm GeV}}
"/>

### `Particle`类

粒子类，`Particle_Base`的子类。定义在头文件`Particle.h`中，部分成员函数实现于`Particle.cpp`中。

#### 定义

    struct Particle : public Particle_Base {
      // ...
    };

#### 相关宏定义

    #define PHASE_UNDEF ((size_t)-1)
    #define PHASE_MIN   ((size_t) 0)