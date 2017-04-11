
#include <gtest/gtest.h>
#include <vehicle.h>

extern std::string DATA_DIR;

class VehiclesTest : public ::testing::Test
{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F( VehiclesTest, time_is_ok )
{
	Vehicle boeng;
	boeng.A.resize(3);
	boeng.A[0] = 0.75*G;
	boeng.A[1] = 0;
	boeng.A[2] = -0.03*G;
	boeng.FC.resize(3);
	boeng.FC[0] = 11.0;
	boeng.FC[1] = 1.0;
	boeng.FC[2] = 0.25;
	boeng.GT = 2600;
	boeng.CV = 915;

	Info i = boeng.complete( 2884 );
	EXPECT_NEAR( 2884, i.distance/1000, 1E-3 ); //km
	EXPECT_NEAR( 3.276, i.time/3600, 1E-3 );    //hours
	EXPECT_NEAR( 8.301, i.fuel/1000, 1E-3 );    //tons
}
