from:http://www.cnblogs.com/itech/archive/2012/03/04/2375746.html
转自：http://coanor.blog.hexun.com/38241166_d.html

 

1. 简介

只要你在Unix环境中写过程序，你必定会邂逅神秘的Lex&YACC，就如GNU/Linux用户所熟知的Flex&Bison，这里的Flex就是由Vern Paxon实现的一个Lex，Bison则是GNU版本的YACC.在此我们将统一称呼这些程序为Lex和YACC.新版本的程序是向上兼容的(译注：即兼容老版本)，所以你可以用Flex和Bison来尝试下我们的实例.
 
这些程序实用性极广，但如同你的C编译器一样，在其主页上并没有描述它们，也没有关于怎样使用的信息.当和Lex结合使用时，YACC实在是棒极了，但是Bison的主页上并没有描述Bison如何跟Lex结合使用以生成代码的相应说明.
 
1.1  本文档『不是』…
有很多非常棒的书籍描述了Lex & Yacc.如果对这些书籍感兴趣，务必加以阅读并加深理解.相比我们，它们总会提供更多的信息.参见文档结尾的”进一步阅读”部分.本文档的目的在于以步步为营的方式教会你使用Lex&Yacc，使得你可以创建你自己的程序.
 
本文档对于Flex和Bison同样适用，但并不是一个关于它们的手册.它们都有自己非常好的HOWTO文档.它们的参考在文档结尾.
 
我并不是一个YACC/Lex专家.当我写这个文档的时候，实际上我只有2天的使用经验.所有我想完成的工作就是让你轻松的度过这两天.
1.2  下载事项
请注意，所有展示的这些实例，你都可以下载，这些都是机器可读(没有加密).更多细节参见主页.
 
2.Lex & YACC能为你做什么？
如果使用得当，这些程序(指LEX&YACC)可以让你轻易的解析复杂的语言，当你需要读取一个配置文件时，或者你需要编写一个你自己使用的语言的编译器时，这对于你来说是莫大的裨益.
 
本文档能提供给你一些帮助，你将发现你再也不用手工写解析器了，Lex & YACC就是为你量身打造的利器.
2.1 每个程序自身是如何工作的？
    虽然这些程序协同工作，但是它们各自的目的不同.下一章将对此加以描述.
 
3. Lex
Lex会生成一个叫做『词法分析器』的程序.这是一个函数，它带有一个字符流传入参数，词法分析器函数看到一组字符就会去匹配一个关键字(key)，采取相应措施.一个非常简单的例子(example1)如下:

%{
#include <stdio.h>
%}
%%
stop       printf(“Stop command received\n”);
start      printf(“Start command received\n”);
%%

第一部分，位于%{和%}对之间直接包含了输出程序(stdio.h).我们需要这个程序，因为使用了printf函数，它在stdio.h中定义.

第二部分用’%%’分割开来，所以第二行起始于’stop’，一旦在输入参数中遇到了’stop’，接下来的那一行(printf()调用)将被执行.

除此之外，还有’start’，其跟stop的行为差不多.

我们再次用’%%’结束代码段.

为了编译上面的例子，只需要执行以下命令：

lex example1.l
cc lex.yy –o example –ll

注意：如果你用flex，则就将lex命令用flex代替，还需要将’-ll’选项改成’-lfl’.在RedHat 6.x以及SuSe中需要这样做.

这样，Lex将生成’example1’这个文件.运行该文件，它将等待你输入一些数据.每次你输入一些不匹配的命令(非’stop’和’start’)，它会将你输入的字符再次输出.你若输入’stop’，它将输出’Stop command received’.

用一个EOF(^D)来结束程序.

也许你想知道，它是怎么运行的，因为我们并没有定义main()函数.这个函数(指main())已经在lib1(liblex)中定义好了，在此我们选用了编译选项’-ll’

3.1 匹配中的正则表达式
这个实例(example2)本身并没什么用处，下一个实例也不会提及正则表达式.但这里它展示了如何在Lex中使用正则表达式，这在后面将非常有用.

%{
#include <stdio.h>
%}

%%
[0123456789]+     printf(“NUMBER\n”);
[a-zA-Z][a-zA-Z0-9]*  printf(“word\n”);

该Lex文件描述了两种token匹配：WORDs和NUMBERs.正则表达式非常恐怖，但是只需要稍花力气便可以加以理解.我们来解说下NUMBER匹配：

[0123456789]+

这意味着：一个只少有一个数字的序列，这些数字来自0123456789组中.我们也可以将其写成：

[0-9]+

现在，WORD匹配就有点复杂：

[a-zA-Z][a-zA-Z0-9]*

第一部分仅仅匹配一个’a’到’z’或’A’到’Z’之间的字符，也即一个字母.接着该字母后面需要连上0个或多个字符，这些字符可以是字母，也可以是数字.这里为何用’*’? ’+’表示至少1次的匹配.一个WORD只有一个字符也可以很好的匹配，在第一部分我们已经匹配到了一个字符，所以第二部分可以是0个匹配，所以用’*’.

用这种方式，我们就模仿了很多编程语言中对于一个变量名的要求，即要求变量名『必须』以字母开头，但是可以在后续字符中用数字.也就是说’temperature1’是一个正确的命名，但是’1temperature’就不是.

像example1一样编译example2，并输入一些文本，如下：

$ ./example2
foo
WORD

bar
WORD

123
NUMBER

bar123
WORD

123bar
NUMBER
WORD

你也许会疑惑，所有的输出中的空格是从哪来的？理由很简单：从输入而来，我们不在空格上匹配任何内容，所以它们又输出来了.

Flex主页上有正则表达式的详细文档.很多人觉得perl正则表达式主页的说明非常有用，但是Flex并不实现perl所实现的所有东西.

你只需要确保不写一些形如’[0-9]*’的空匹配即可，你的词法分析器(由Flex生成)将不明就里的开始不断的匹配空字符.

3.2 复杂一点的类C语法示例
假定我们需要解析一个形如下面的文件：

logging{
    category lame-servers { null; };
    category cname { null; };
};

zone “.” {
    type hint;
    file “/etc/bind/db.root”;
}

我们在此见到了很多token：
WORD: 如’zone’和’type’
FILENAME：如“/etc/bind/db.root”
QUOTE: 如包含文件名的引号
OBRACE：{
EBRACE:  }
SEMICOLON:  ;

example3相应的Lex文件如下：

%{
#include <stdio.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]*      printf(“WORD ”);
[a-zA-Z0-9\/.-]+         printf(“FILENAME ”)
\”                    printf(“QUOTE ”);
\{                    printf(“OBRACE ”);
\}                    printf(“EBRACE ”);
;                     printf(“SEMICOLON ”);
\n                    printf(“\n”);
[ \t]+                /* ignore whitespace */;
%%

当输入我们的文件到Lex生成的example3中，我们得到：
 WORD OBRACE
WORD FILENAME OBRACE WORD SEMICOLON EBRACE SEMICOLON
WORD WORD OBRACE WORD SEMICOLON EBRACE SEMICOLON
EBRACE SEMICOLON
WORD QUOTE FILENAME QUOTE OBRACE
WORD WORD SEMICOLON
WORD QUOTE FILENAME QUOTE SEMICOLON
EBRACE SEMICOLON

4. YACC
YACC可以解析输入流中的标识符(token)，这就清楚的描述了YACC和LEX的关系，YACC并不知道『输入流』为何物，它需要事先就将输入流预加工成标识符，虽然你可以自己手工写一个Tokenizer，但我们将这些工作留给LEX来做。

YACC用来为编译器解析输入数据，即程序代码.这些用编程语言写成的程序代码一点也不模棱两可——它们只有一个意思.正因为如此，YACC才不会去对付那些有歧义的语法，并且会抱怨shift/reduce或者reduce/reduce冲突.更多的关于模糊性和YACC『问题』可以在『冲突』一章中找到.

4.1 一个简单的温度控制器
假定我们有一个温度计，我们要用一种简单的语言来控制它.关于此的一个会话、如下：

heat on
    Heater on!
heat off
    Header off!
target temperature set!

我们需要识别的标识符为heat, on/off(STATE), target, temperature, NUMBER.

LEX的tokenizer(example4)为：

%{
#include <stdio.h>
#include “y.tab.h”
%}

%%
[0-9]+         return NUMBER;
heat           return TOKHEAT;
on|off         return STATE;
target         return TOKTARGET;
temperature    return TOKTEMPERATURE;
\n             /* ignore end of line */;
[ \t]+         /* ignore whitespace */
%%

有两个重点需要注意. 第一，我们包含了『y.tab.h』，第二，我们不再打印输出了，我们返回标识符的名字.之所这样做是因为我们将这些返回传送给了YACC，而它对于我们屏幕上的输出并不感冒. 『y.tab.h』中定义了这些标识符.

但是y.tab.h从哪里来？它由YACC从我们编写的语法文件中生成，语法文件非常简单，如下：

commands: /* empty */
    | commands command
;

command: heat_switch
    | target_set
;

heat_switch:
    TOKHEAT STATE
    {
        printf(“\tHeat turned on or off\n”);
    }
;

target_set:
    TOKTARGET TOKTEMPERATURE NUMBER
    {
        printf(“\tTemperature set\n”);
    }
;

第一部分，我们称之为根(root).它告诉我们有一个『commands』，并且这些『commands』由单个的『command』组成.正如你所见到的那样，这是一个标准的递归结构，因为它又再次包含了『commands』.这意味着该程序可以一个个的递减一系列的命令.参见『YACC和LEX内部是如何工作的』一章，阅读更多的递归细节.

第二个规则定义了『command』的内容.我们只假定两种命令.

一个heat_switch由HEAT标识符组成，它后面跟着一个状态，该状态在LEX中定义，为『on』或『off』.

target_set稍微有点复杂，它由TARGET标识符、TEMPERATURE以及一个数字组成.

一个完整的YACC文件
前面的那个例子只有YACC文件的语法部分，起始在YACC文件中还有其它内容，那就是我们省略的文件头部分：

%{
#include <stdio.h>
#include <string.h>

void yywrap()
{
    return  1；
}

main()
{
    yyparse();
}
%}

%token  NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

函数yyerror()在YACC发现一个错误的时候被调用，我们只是简单的输出错误信息，但其实还可以做一些更漂亮的事情，参见文档尾的『进阶阅读』部分.

yywrap()函数用于不断的从一个文件中读取数据，当遇到EOF时，你可以再输入一个文件，然后返回0，你也可以使得其返回1，暗示着输入结束.更多细节，参见『YACC和LEX内部如何工作的？』一章.

接着，这里有一个main()函数，它基本什么也不做，只是调用一些函数.

最后一行简单的定义了我将使用的标识符，如果调用YACC时，使用『-d』选项，那么它们会输出到y.tab.h中.

编译并运行恒温控制器
lex example4.l
yacc  –d   example4.y
cc  lex.yy.c      y.tab.c    –o  example4

在此，情况有所改变，我们现在调用YACC来编译我们的程序，它创建了y.tab.c和y.tab.h. 我接着再调用LEX. 编译时，我们去除了『-ll』编译选项，因为此时我们有了自己的main()函数，并不需要libl来提供.

注意：如果在编译过程中报错说找不到『yylval』，那么在example4.l的#include <y.tab.h>下面加上：

extern YYSTYPE yylval；

具体细节在『YACC和LEX内部是如何工作的?』中解说.

一个简单的会话：
$ ./example4
heat on
    Heat turned on or off
heat off
    Heat turned on or off
target temperature 10
    Temperature set
target humidity 20
error: parse error
$

4.2 扩展恒温器，使得其可以接受参数
我们已经可以正确的解析温度计命令了，并且能对一些错误做标记.但也许一些狡猾的人会猜疑说，该解析器并不知道你应该做什么，也没有处理一些你输入的数值.

让我们来添加能读取新的温度参数的功能.为达到此目的，我们得知道LEX中的NUMBER匹配要转化成一个数值，然后才能为YACC所接收.

每当LEX匹配到了一个目标字串，它就将该匹配文本赋值给『yytext』，YACC则依次在『yylval』中来查找一个值，在example5中，我们可以得到一个明晰的方案：

%{
#include <stdio.h>
#include “y.tab.h”
%}
%%
[0-9]+     yylval = atoi(yytext); return NUMBER;
heat           return TOKHEAT;
on|off     yylval = !strcmp(yytext, “on”); return STATE;
target     return TOKTARGET;
temperateure   return TOKTEMPERATURE;
\n         /* ignore end of line */
[ \t]+     /* ignore whitespace */
%%

如你所见，我们在yytext中用了atoi()，并将结果存储在yylval中，使得YACC可以『看见』它. 同理，我们再处理STATE匹配，将其与『on』比较，若想等，则将yylval设置为1.

接下来，我们就得考察YACC如何来应对.我们来看看新的temperature target规则设置：

target_set:
    TOKTARGET TOKTEMPERATURE NUMBER
    {
        printf(“\tTemperature set to %d”, $3);
    }
    ;

为得到规则中第三部分的值(NUMBER)，我们用『$3』来表示，每次yylex()返回时，yylval的值便依附到了终结符上，其值可以通过『$-常数』来获取.

为更进一步加深理解，我们来看『heat_switch』规则：
heat_switch:
    TOKHEAT STATE
    {
        if ($2)
            printf(“\tHeat turned on\n”);
        else
            printf(“\tHeat turned off\n”);
    }

如果现在运行example5，它将输出你所输入的数据.

4.3 解析一个配置文件
让我们再次回顾先前提到的那个配置文件：

zone  “.”  {
    type  hint;
    file  “/etc/bind/db.root”;
};

之前我们已经将LEX文件写好了，接下来只需要编写YACC语法文件，并且对词法分析器做一些修改，使得其可以返回一些值给YACC.
example6中的词法分析器如下：

%{
#include <stdio.h>
#include “y.tab.h”
%}
%%
zone       return  ZONETOK;
file           return  FILETOK;
[a-zA-Z][a-zA-Z0-9]*     yylval = strdup(yytext);  return  WORD;
[a-zA-Z0-9\/.-]+         yylval = strdup(yytext);  return  FILENAME;
\”         return  QUOTE;
\{         return  OBRACE;
\}         return  EBRACE ;
;              return  SEMICOLON;
[ \t]+     /* ignore whitespace */;
\n         /* ignore EOL */;
%%

细心的话，你会发现yylval已经改变了！我们不再认为它是一个整数，而是假定为一个char*类型数据.为保持简单性，我们调用strdup并因此耗费了很多内存.但这并不影响你解析这个文件.

我们需要保存字符串的值，在此我们处理的都是一些命名，文件名以及区域命.在下一章，我们将解说如何对付一些复杂类型的数据.

为通知YACC关于yylval的新类型，我们在YACC的语法文件中添加一行：

#define YYSTYPE  char *

语法自身也变得更加复杂.我们将其分割出来，以便慢慢消化：

commands  :
    | commands command SEMICOLON
;
command  :
    zone_set
;
zone_set  :
    ZONETOK quotedname zonecontent
    {
        printf(“Complete zone for ‘%s’ found\n”, $2);
    }
;

这里包含了前面提到的那个『root』递归结构. 继续：

zonecontent  :  OBRACE  zonestatements  EBRACE
quotedname  :  QUOTE  FILENAME  QUOTE
                  {
                      $$ = $2;
                  }
这里定义了『quotedname』，这里值得注意的是，quotedname的值就是FILENAME的值.

zonestatements  : zonestatements  zonestatement  SEMICOLON
;
zonestatement  : statements 
                | FILETOK quotedname
                  {
                      printf(“A zonefile name ‘%s’ was encountered\n”, $2);
                  }
;

在这里，我们又看到了递归结构.

block  : OBRACE  zonestatements EBRACE  SEMICOLON
;
statements  :   statements  statement
;
statement  ； WORD | block | quotedname
;
这里则定义了一个块(block)，其中有『statements』定义.

我们执行example6的输出文件：

$  ./example6
zone “.” {
    type  hint;
    file  “/etc/bind/db.root”;
    type  hint；
}

输出为： 
A zonefile name ‘/etc/bind/db.root’ was encountered
Complete zone for ‘.’ found
 
5. 用C++做一个解析器
虽然LEX和YACC的历史要早于C++，但是还是可以用它们来生成一个C++解析器.但我们用LEX来生成C++的词法分析器，YACC并不知道如何直接来处理这些，所以我们不打算这么做.

我认为比较好的做法是，要做一个C++解析器，就需要LEX生成一个C文件，并且让YACC来生成C++代码.但当你这么做的时候，在这个过程中你将会遇到问题，因为C++代码默认情况下并不能找到C的函数，除非你将那些函数定义为extern “C”.

为达此目的，我们在YACC代码中编写一个C开头：

extern “C”
{
    int yyparse(void);
    int yylex(void);
    int yywrap()
    {
        return 1;
    }
}

如果你想声明并改变yydebug函数，你得这样做：
extern int yydebug;
main()
{
yydebug = 1;
yyparse();
}

这是因为C++中的一个关于定义的规则，即不允许yydebug的多处定义.

你还可能发现，你需要在你的LEX文件中重复#define YYSTYPE，这是由于C++中严格的类型检查(机制)造成的.

按照如下方式来编译：

lex bindconfig2.1
yacc –verbose –debug –d bindconfig2.y –o bindconfig2.cc
cc –c lex.yy –o lex.yy.o
c++ lex.yy.o bindconfig2.cc –o bindconfig2

由于-o选项的存在，y.tab.h现在变成bindconfig2.cc.h，记住这点.

总结： 不要自寻烦恼的在C++中编译你的词法分析器，让它呆在C的领地里.在C++中编写解析器时，(也得)确保向编译器解释清楚，即你的C函数都有一个extern “C”声明.
 
6.Lex和YACC内部是如何工作的？
在YACC文件中，你定义了你自己的main()函数，它在某个点上调用了yyparse().YACC会创建你的yyparse()函数，并在y.tab.c中结束该函数.

yyparse()函数读取一个『标识符/值对』(token/value pairs)流，这些流需要事先就提供，这些流可以是你自己手写的代码提供的，也可以是LEX生成的.在我们的示例中，我们把这个工作丢给了LEX.

LEX生成的yylex()函数从文件参数FILE *file中读取字符(文件名为yyin).如果不设置成yyin，则默认为标准输入，它会输出到yyout中，如果不加设置，就是stdout.你可以在yywrap()函数中修改位于文件尾的yyin.yywrap()函数.这些修改使得你可以打开另一些文件，并继续解析.

如果是这种情况，那么就让yywrap()返回0，如果你想在该文件上结束解析，就让它返回1.

每次yylex()调用都会返回一个整数值，该值代表了一个标识符类型(token type).它告诉YACC，已经读取了这种标识符.该标识符可以有一个值，它应该存放在yylval变量中.

yylval的默认类型为int,但是你可以修改其类型，通过在YACC文件中#define YYSTYPE.

词法分析器需要能够访问yylval，为达到此效果，(yylval)必须在词法分析器(lexer)中被声明为一个外部变量(extern variable).原来的YACC忽略了这点，并没有为你干这项工作，所以，你必须添加以下代码到你的词法分析器中，就在#include <y.tab.h>下面：

extern YYSTYPE yylval;

当今多数人使用的Bison已经为你把这事自动做好了.

6.1 标识符的值(token values)
在前面我已经说过，yylex()需要返回它遇到了一个什么标识符类型，并将其值存储在yylval中.当这些标识符在%token命令中定义时，它们就被赋予了一些数字ID，从256开始.

由于这个事实，(我们)可以将所有的ascii字符当作标识符.假定你要写一个计算器，到现在为止，我们可能已经这样写了其词法分析器：

[0-9]+     yylval = atoi(yytext); return NUMBER;
[ \n]+     /* eat whitespace */
-          return MINUS;
\*         return MULT;
\+         return PLUS;
…

YACC文件可能是这样：

exp ； NUMBER
       | exp PLUS exp
       | exp MINUS exp
       | exp MULT exp
…

没有必要弄这么复杂.用字符作为速记法来作为标识符的数字ID，我们可以这样来重写我们的词法分析器：

[0-9]+        yylval = atoi(yytext); return NUMBER;
[ \n]+        /* eat whitespace */
.             return (int) yytext[0];

最后一行匹配任何的单个字符，否则就是不匹配字符.

而YACC的语法文件则是这样:

exp : NUMBER
       | exp ‘+’ exp
       | exp ‘-’ exp
       | exp ‘*’ exp
 
这样更加简短而直观，你就不必在文件头用%token来定义那些ascii字符了.
 
另一方面，这样构造还有一些好处，它可以匹配所有丢给它的东西，而避免了将那些不匹配的输入输出到标准输出的默认行为.如果用户在当前计算器上输入一个’^’字符，将会导致一个解析错误，而不是将其输出到标准输出中.
 
6.2 递归：’right is wrong’
递归是YACC一个极其重要的特性.没有递归的话，你就确定一个文件是由一系列独立的命令组成还是由语句组成.由于YACC自身的特性，它只对第一个规则或那个你将其设计为『起始规则』的规则感兴趣.起始规则用’%start’符号标记.

YACC中的递归以两种形式出现，左递归和右递归.左递归是你应该经常使用的，它们看起来如下：

Commands ： /* empty */
       | commands command

这是在说，一个command要么为空，要么它包含了更多的commands，后面再跟一个command.YACC的这种工作方式意味着它现在可以轻易的剔除单个的command群并一步步简化(处理).
 
拿上面的例子和下面的右递归做比较：
 
Commands : /* empty */
       | command commands
但是这样做开销有点大，如果(commands)是%start规则(即起始规则)，那么YACC会将所有的commands保存在你的栈数据中(file on the stack)，这将耗费大量内存.所以，在解析长的语句时，务必使用左递归，例如整个文件.但有时难以避免右递归，不过，如果你的语句并不太长，你就没有必要越轨使用左递归.

如果你有一些东西来终结(因此而分割)你的commands，右递归就非常适合了，但开销还是有点大:
 
Commands : /* empty */
    | command SEMICOLON commands
 
正确的做法是使用左递归(这也不是我发明的)：

commands : /* empty */
    | commands command SEMICOLON
 
本文档的早期版本错误的使用了右递归.Markus Triska友好的提示我们这点(错误).
 
6.3 高级yylval: %union
现在，我们需要定义yylval的类型.但是这并不一直恰如其当.我们可能会多次这样做，因为需要处理多种数据类型.回到我们假定的那个恒温器，可能你想选择控制一个加热器，例如：

heater mainbuilding
    Selected ‘mainbuilding’ heater
Target temperature 23
    ‘mainbuilding’ heater target temperature now 23
 
这样的话，就要求yylval是一个union，它可以存储字符串，也可以存储整数，但并不是同时存储.
 
回忆之前我们讲过，我们提前通知YACC哪种yylval类型会要处理是通过定义YYSTYPE来实现.同样，我们可以定义YYSTYPE为一个union，YACC中有一种简便的方法来实现，即%union语句.
 
在example4基础上，我编写example7的YACC语法：
 
%token TOKHEATER TOKHEAT TOKTARGET TOKTEMERATURE
%union
{
    int number;
    char *string;
}
%token <number> STATE
%token <number> NUMBER
%token <string> WORD
 
我们定义了union，它只包含一个整数和一个字符串.接着使用了一个扩展的%token语法，我们向YACC解释了应该获取union哪个部分的标识符.
 
在本例中，我们让STATE标识符用一个整数(来表示)，这跟之前一样.NUMBER同理，我们之前用来读取温度.
 
但是WORD有所改变，它声明为需要一个字符串.
 
词法解析器文件有所改变：
 
%{
#include <stdio.h>
#include <string.h>
#include “y.tab.h”
%}
%%
[0-9]+     yylval.number=atoi(yytext); return NUMBER;
heater     return TOKHEATER;
heat       return TOKHEAT;
on|off     yylval.number = ！strcmp(yytext, “on”); return STATE;  
target     return TOKTARGET;
temperature   return TOKTEMPERATURE;
[a-z0-9]+     yylval.string = strdup(yytext); return WORD;
\n            /* ignore end of line */
[ \t]+        /* ignore whitespace */
%%
 
正如你所见，我们不再直接访问yylval，我们添加了一个后缀来说明我们要访问那个部分.我们不再需要在YACC语法文件中来干这个工作，YACC在这里耍了下魔法：
 
heater_select :
    TOKHEATER WORD
    {
       printf(“\tSelected heater ‘%s’\n”, $2);
       heater = $2;
}
    ;
 
由于上面的%token声明，YACC自动选择了union中的’string’成员.注意这里$2中存储的一份拷贝，在后面它会告诉用户发送命令到哪个heater：
 
target_set
    TOKTARGET TOKTEMPERATURE NUMBER
    {
       printf(“\tHeater ‘%s’ temperature set to %d\n”, heater, $3);
}
;
 
7.调试
YACC中有许多调试反馈信息.这些调试信息的代价有点高，所以你需要提供一些开关来打开它.

当调试你的语法时，在YACC命令行中添加—debug和—verbose选项，在你的C文件头中添加以下语句：
int yydebug = 1;
 
这将生成一个y.output文件，其中说明了所创建的那个状态机.
 
当你运行那个生成的二进制文件，它将输出很多运行时信息.里面包含当前所运行的状态机以及读取到的一些标识符.

Peter Jinks写了一篇关于调试的文章，他在其中讲述了一些常见得错误以及如何修正这些错误.

7.1 状态机
YACC解析器在内部运行的是一个『状态机』，该状态机可以有多种转台.接着有多个规则来管制状态间的相互转化.任何内容都是从『root』规则开始.

在example7的y.output文件中：

state 0
    ZPONETOK   , and go to state 1
    $default   reduce using rule 1 (commands)
    commands   go to state 29
    command    go to state 2
    zone_set   go to satte 3
 
默认情形下，这个状态机从『commands』规则开始递减演化，这也是我们之前的那个递归规则，它定义了『commands』并从单个的『command』进行构造，后面跟着一个分号，然后可能再跟着更多的『commands』.

这个状态机不断递减演化，直到它遇到某些它能理解的东西，在本例中，为一个ZONETOK，也即单词『zone』.然后转化到状态1，在此，进一步处理一个zone command:
 
state 1
    zone_set   ->     ZONETOK .quotedname zonecontent (rule 4)
    QUOTE      ,      and go to state 4
    Quotedname go to state 5
 
第一行中有一个『.』，它用来说明我们所处的位置：即刚刚识别到了一个ZONETOK，目前正在寻找一个『quotedname』.显然，一个『quotedname』会以QUOTE开始，它将我们转化到状态4.
 
为进一步跟踪，用在『调试』章节中提到的标志来编译example7.
 
7.2 冲突：『shift/reduce』以及『reduce/reduce』
一旦YACC警告你出现了冲突，那么你的麻烦来了.要解决这些问题显得是一种技巧形式，它会教会很多关于你的语言的东西.比你想知道的要多的多的内容.

问题萦绕于如何来翻译一系列标识符.假定我们定义了一种语言，它需要接受一下两种命令：
 
delete heater all
delete heater number1
 
为达到此目的，我们的语法为：
 
delete_heaters :
    TOKDELETE TOKHEATER mode
    {
       Deleteheaters($3);
}
mode : WORD
 
delete_a_heater:
    TOKDELETE TOKHEATER WORD
    {
       delete($3);
}
 
也许你已经嗅到了麻烦的味道.状态机从读取单词『word』开始，接着它根据下一个标识符觉得转换到何种状态.接下来的标识符可以是『mode』，它指定了如何来删除heater，或者是将要删除的heater.
 
然而这里的麻烦是，对于这两个命令，下一个标识符都将是一个WORD.YACC因此也无法决定下一步该干嘛.这回导致一个『reduce/reduce』警告，而下一个警告就是『delete_a_heater』节点在状态转化图中永远也不能达到.
 
这种情况的冲突容易解决(例如，重命名第一个命令为『delete all heater』，或者将『all』作为一个分开的标识符)，但有时，(要解决冲突)却非常困难. 通过『--verbose』参数生成的y.output文件可以提供给你极大的帮助.
 
8.进一步阅读
GNU YACC(Bison)有一个非常棒的.info文件，在其中很好的记录了YACC的语法.其中只提到了一次LEX，然而它还是很棒的.你可以用Emacs中那个非常好的『pinfo』工具阅读.info文件.同时，在Bison的主页上可以获得它：Bison手册.
 
FLEX有一个不错的主页.如果你粗略了解了FLEX所作所为，那将是非常有益的.FLEX的手册也可以联机获取.
 
在这些关于YACC和LEX的介绍之后，你可能觉得你想需要更多的信息.下面的书籍我们都还没有阅读，但他们听起来不错：
 
Bison—The Yacc-Compitible Parser Generator
    ——Charles Donnelly && Richard Stallman.
Lex & Yacc
    ——John R. Levine, Tony Mason ,Doug Brown.
Compilers: Principles, Techniques, and Tools
    ——By Alfred V.Aho,Ravi