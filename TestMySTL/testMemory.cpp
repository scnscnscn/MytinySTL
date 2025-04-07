#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Memory.h"

namespace mystl {

	// ≤‚ ‘ address_of ∫Ø ˝
	TEST(MemoryTest, AddressOf) {
		int x = 42;
		int* addr = address_of(x);
		EXPECT_EQ(addr, &x);
	}

	// ≤‚ ‘ get_temporary_buffer ∫Õ release_temporary_buffer ∫Ø ˝
	TEST(MemoryTest, GetAndReleaseTemporaryBuffer) {
		auto buffer = get_temporary_buffer<int>(10);
		EXPECT_NE(buffer.first, nullptr);
		EXPECT_EQ(buffer.second, 10);

		release_temporary_buffer(buffer.first);
	}

	// ≤‚ ‘ temporary_buffer ¿‡
	TEST(MemoryTest, TemporaryBuffer) {
		std::vector<int> vec(10, 1);
		temporary_buffer<std::vector<int>::iterator, int> temp_buf(vec.begin(), vec.end());

		EXPECT_EQ(temp_buf.size(), 10);
		EXPECT_EQ(temp_buf.requested_size(), 10);
		EXPECT_NE(temp_buf.begin(), nullptr);
		EXPECT_NE(temp_buf.end(), nullptr);
	}

	// ≤‚ ‘ auto_ptr ¿‡
	TEST(MemoryTest, AutoPtr) {
		auto_ptr<int> p1(new int(42));
		EXPECT_EQ(*p1, 42);

		auto_ptr<int> p2(p1);
		EXPECT_EQ(p1.get(), nullptr);
		EXPECT_EQ(*p2, 42);

		auto_ptr<int> p3;
		p3 = p2;
		EXPECT_EQ(p2.get(), nullptr);
		EXPECT_EQ(*p3, 42);

		p3.reset(new int(100));
		EXPECT_EQ(*p3, 100);
	}

}  // namespace mystl

//int main(int argc, char** argv) {
//	::testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "MemoryTest.*";
//	return RUN_ALL_TESTS();
//}
