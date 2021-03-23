# Texas_Holdem_Poker_1v1_AI
Building an AI to play 1v1 Poker

目前只能单人操纵两个玩家进行1v1

游戏标准是1/2 100BB

每手牌打完后都会双方自动重置到100BB

游戏开始后，每一个action需要输入一个数

这个数的大小为【0，200】

0就代表check/fold

其余的数就代表下注或者跟注

其中如果下了和另一个选手一样的注，就意味着跟注
也就是说这里的下注是至将本轮下注筹码量补至多少

下注非翻牌前的下注轮次时，需要注意不能超过remaining stack

一个例子（不要在意下注逻辑，咳咳）：

New Game Started!!!

Player_1 Cards: 4d 6d
Player_2 Cards: Qs As

Player_2 Small Blind: 1
Player_1 Big Blind: 2
Player_2 Action: 2
Player_1 Action: 2

Player 1 Remaining Stack: 198
Player 2 Remaining Stack: 198

Flop: 5d 2c Jd
Player_1 Action: 0
Player_2 Action: 0

Player 1 Remaining Stack: 198
Player 2 Remaining Stack: 198

Turn: 5d 2c Jd Jc
Player_1 Action: 5
Player_2 Action: 10
Player_1 Action: 10

Player 1 Remaining Stack: 188
Player 2 Remaining Stack: 188

River: 5d 2c Jd Jc Ad
Player_1 Action: 0
Player_2 Action: 30
Player_1 Action: 70
Player_2 Action: 188
Player_1 Action: 0
Winner: 2
Value: 82

Player 1 Total Value: -82
Player 2 Total Value: 82



另一个例子（统计了上一个例子的盈亏）：

New Game Started!!!

Player_1 Cards: 7s Ac
Player_2 Cards: 7d Qh

Player_2 Small Blind: 1
Player_1 Big Blind: 2
Player_2 Action: 200
Player_1 Action: 200

Player 1 Remaining Stack: 0
Player 2 Remaining Stack: 0

Flop: 8h 3s Td

Player 1 Remaining Stack: 0
Player 2 Remaining Stack: 0

Turn: 8h 3s Td 4h

Player 1 Remaining Stack: 0
Player 2 Remaining Stack: 0

River: 8h 3s Td 4h 8s
Winner: 1
Value: 200

Player 1 Total Value: 118
Player 2 Total Value: -118
