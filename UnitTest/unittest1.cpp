#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\include\TankMind.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{	
	public:

		TEST_METHOD(Test1)
		{
			TankMind* Tank;

			bool expectedValue = false;
			bool actualValue = Tank->bIsMoving;

			Assert::AreEqual(expectedValue, actualValue, L"MESSAGE", LINE_INFO());
		}

		TEST_METHOD(getDistanceCalculation)
		{
			TankMind* Tank;

			float expectedValue = 3.16;
			float actualValue = getDistance(2.f, 5.f, -1.f, 6.f);

			Assert::AreEqual(expectedValue, actualValue, 0.01f, L"MESSAGE", LINE_INFO());
		}

		TEST_METHOD(getDistancePositionsCalculation)
		{
			Position pos1(2.f, 7.f);
			Position pos2(-1.f, 6.f);

			float expectedValue = 3.16;
			float actualValue = getDistance(pos1, pos2);

			Assert::AreEqual(expectedValue, actualValue, 0.01f, L"MESSAGE", LINE_INFO());
		}

		TEST_METHOD(findMatchTest)
		{
			Position pos1(500.f, 500.f);
			Position pos2(330.f, 220.f);
			Position pos3(1024.f, 768.f);
			Position pos4(500.f, 500.f);

			std::vector<Position> vPositions = { pos2, pos3, pos4 };

			bool expectedValue = true;
			bool actualValue = findMatch(pos1, vPositions);

			Assert::AreEqual(expectedValue, actualValue, L"MESSAGE", LINE_INFO());
		}

		TEST_METHOD(findMatchFalse)
		{
			Position pos1(800.f, 600.f);
			Position pos2(1920.f, 1080.f);
			Position pos3(1024.f, 768.f);
			Position pos4(1600.f, 1080.f);

			std::vector<Position> vPositions = { pos2, pos3, pos4 };

			bool expectedValue = false;
			bool actualValue = findMatch(pos1, vPositions);

			Assert::AreEqual(expectedValue, actualValue, L"MESSAGE", LINE_INFO());
		}

		TEST_METHOD(rotationDiffTest)
		{
			Position pos1(0.f, 6.f);
			Position pos2(0.f, 0.f);

			float expectedValue = 180.f;
			float actualValue = rotationDiff(pos1, pos2, 90.f);

			Assert::AreEqual(expectedValue, actualValue, 0.01f, L"MESSAGE", LINE_INFO());
		}

		/*TEST_METHOD(NodesTest)
		{
			TankMind* Tank;

			BehaviourTree::Selector *root;
			CheckShell *checkShell;
			CheckEnemy *checkEnemy;
			CheckEnemyBase *checkEnemyBase;
			CheckPatrol *checkPatrol;

			root->addChild(checkShell);
			root->addChild(checkEnemy);
			root->addChild(checkEnemyBase);
			root->addChild(checkPatrol);
		}
		*/
		
	};
}