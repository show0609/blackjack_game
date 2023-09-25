# 21點遊戲

### 遊戲規則
#### 21點基本規則
- 每副牌的構造如下:
    - 有黑桃、愛心、方塊、梅花四種花色
    - 每種花色有 1 2 3 4 5 6 7 8 9 10 J Q K，1 可由玩家選擇代表 1 或 11點，J Q K 點數都為10點，其於牌的點數為自身大小
- 爆牌:
    點數大於21點
- 過五關:
    抽五張牌(點數不大於21點)

#### 獲勝規則
- 輸贏:
    - 點數大者獲勝(過五關為最贏，爆牌最輸，其他情況點數大者獲勝)
    - 若玩家和莊家點數結果，視為玩家輸
- 賭金:
    - 玩家贏由莊家給予和賭金同值的錢
    - 玩家輸則賭金被莊家收走

#### 其他規則
- 遊戲人數:
    - 不限制參與人數，每4人會使用一副牌(不滿4人以4人計)
    - 每局遊戲只會有一位莊家，資金為 $10000
    - 若參與遊戲賭金最低 $1，也可以選擇不參加賭局
    - 玩家可以向莊家借錢，資金可以為為負數

- 遊戲流程:
    1. 玩家資訊設置:
        先設置玩家人數、再依序設置玩家種類(Human, Meek, Random)、姓名、資金，設置完後即進入每局遊戲

    2. 每局遊戲:
        (1) 每位玩家對本局遊戲下注
        (2) 每個玩家(含莊家)發2張牌，其中一張會翻開，如果牌庫總量低於玩家數 * 5 ，則將牌回收並重新洗牌
        (3) 每個玩家(含莊家)決定是否要追加牌
        (4) 公布參與此次賭局的玩家的輸贏
        (5) 公布目前每個玩家的資金
        (6) 決定是否進行下一局遊戲


### 電腦玩家行為
#### Meek
- 下注
    以 $2 開始，每三連贏則乘二
    第一次爆牌後的下一次賭金退回 $2
- 抽牌
    若目前點數為偶數或擁有方塊7抽牌，否則不抽牌
#### Random
- 下注
    隨機下注(賭金範圍為 $1 ~ 資金的一半)
    若資金小於 $2 即無法再下注
- 抽牌
    依據目前點數有不同機率
    0 - 9 點 : 100%
    10-12 點: 80% 
    13-15 點: 70% 
    16-18 點: 50%
    < 19 點: 0%
#### Dealer (莊家)
- 抽牌
    依據目前點數有不同機率
    0-16 點 : 100%
    < 17 點 : 0%

※電腦玩家行為以最小點數做為判斷
ex: Random 玩家有 card 1 (point 1 or 11), 以 point 1 作為行為判斷(有100%抽牌機率)


### Reference
Inheritance:
    https://www.studytonight.com/cpp/order-of-constructor-call.php
new:
    https://openhome.cc/Gossip/CppGossip/newDelete.html
vector:
    https://mropengate.blogspot.com/2015/07/cc-vector-stl.html
    https://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-vector
    https://stackoverflow.com/questions/12702561/iterate-through-a-c-vector-using-a-for-loop
Header Guard:
    https://blog.csdn.net/qq_27278957/article/details/77988256
string slicing:
    https://m.cplusplus.com/reference/string/string/substr/
random number:
    https://blog.gtwang.org/programming/c-cpp-rand-random-number-generation-tutorial-examples/
enum:
    https://blog.jaycetyle.com/2018/09/c-xmacro/
int to str:
    https://www.delftstack.com/zh-tw/howto/cpp/how-to-convert-int-to-string-in-cpp/
typeid:
    https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c
static_cast
    https://stackoverflow.com/questions/2436125/c-access-derived-class-member-from-base-class-pointer
