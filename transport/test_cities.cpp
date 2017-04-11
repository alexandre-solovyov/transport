
#include <gtest/gtest.h>
#include <cities.h>
#include <tools.h>

extern std::string DATA_DIR;

class CitiesTest : public ::testing::Test
{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F( CitiesTest, city_is_valid )
{
	City c;

	c = City( "" );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name ) );

	c = City( "test" );
	ASSERT_TRUE ( c.isValid() );
	ASSERT_EQ( std::string( "test" ), toS( c.name ) );

	c = City( " " );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name ) );

	c = City( "  " );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name ) );

	c = City( "  abc d " );
	ASSERT_TRUE( c.isValid() );
	ASSERT_EQ( std::string( "abc d" ), toS( c.name ) );
}

TEST_F( CitiesTest, loading_is_ok )
{
	Cities c;
	ASSERT_EQ( 0, c.size() );

	ASSERT_FALSE( c.load( "not_existing.dat" ) );
	ASSERT_EQ( 0, c.size() );

  ASSERT_TRUE( c.load( DATA_DIR + "cities_test.dat" ) );
	ASSERT_EQ( 3, c.size() );
}

TEST_F( CitiesTest, finding_is_ok )
{
	Cities cc;
  ASSERT_TRUE( cc.load( DATA_DIR + "cities_test.dat" ) );
	ASSERT_EQ( 3, cc.size() );

	City c = cc.find( toW( "Moscow" ) );
	ASSERT_EQ( toW( "ru" ), c.country );
	ASSERT_EQ( toW( "Moscow" ), c.name );
	ASSERT_EQ( 10381288, c.population );
	EXPECT_NEAR( 55.752222, c.latitude, 1E-3 );
	EXPECT_NEAR( 37.615556, c.longitude, 1E-3 );
}
