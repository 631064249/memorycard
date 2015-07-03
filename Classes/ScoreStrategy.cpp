
#include "ScoreStrategy.h"
#include "cocos2d.h"
#include "ScoreData.h"
#include "Card.h"
ScoreStrategy::ScoreStrategy() :_continuous(0)
{

}

void ScoreStrategy::execute(ScoreData* score, CardData* cardA, CardData* cardB)
{
	if (cardA->number == cardB->number) {
		//配对成功，增长能量 累计连击数
		_continuous++;
		if (_continuous>score->maxContinuous) {
			//赋予最大连击数
			score->maxContinuous = _continuous;
		}
		score->energy += 50;

		//我们的分数成倍增加
		score->score += 50 * _continuous;
	}
	else{
		//配对失败

		if (cardA->flipcount == 0 && cardB->flipcount == 0)
		{
			//第一次翻开不扣能量

		}
		else{
			//不是第一次翻开 扣能量
			score->energy -= 10;

			//清除连击数
			_continuous = 0;
		}
	}
	cardA->flipcount++;
	cardB->flipcount++;
}