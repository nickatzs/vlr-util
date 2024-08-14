#include "pch.h"

#include "vlr-util/util.convert.StringConversion.h"
#include "vlr-util/zstring_view.h"
#include "vlr-util/StringCompare.h"

TEST( util_convert_StringConversion, general )
{
	using namespace vlr::util;

	constexpr auto pcaszTestString = "TestString";
	constexpr auto pcwszTestString = L"TestString";
	constexpr auto pcszTestString = _T("TestString");

	const auto straTest = std::string{ pcaszTestString };
	const auto strwTest = std::wstring{ pcwszTestString };
	const auto svaTest = std::string_view{ straTest };
	const auto svwTest = std::wstring_view{ strwTest };
	const auto svzaTest = vlr::zstring_view{ straTest };
	const auto svzwTest = vlr::wzstring_view{ strwTest };
	const auto saTest = CStringA{ pcaszTestString };
	const auto swTest = CStringW{ pcwszTestString };
	const auto bsTest = _bstr_t{ pcwszTestString };

	auto fTestConvertToAllTargetTypes = [&]( const auto& tString )
	{
		// to std::string

		auto tString_asStdStringA = Convert::ToStdStringA( tString );
		EXPECT_STREQ( tString_asStdStringA.c_str(), pcaszTestString );
		auto tString_asStdStringW = Convert::ToStdStringW( tString );
		EXPECT_STREQ( tString_asStdStringW.c_str(), pcwszTestString );
		auto tString_asStdStringT = Convert::ToStdString( tString );
		EXPECT_STREQ( tString_asStdStringT.c_str(), pcszTestString );

		// to CString

		auto tString_asCStringA = Convert::ToCStringA( tString );
		EXPECT_STREQ( tString_asCStringA, pcaszTestString );
		auto tString_asCStringW = Convert::ToCStringW( tString );
		EXPECT_STREQ( tString_asCStringW, pcwszTestString );
		auto tString_asCStringT = Convert::ToCString( tString );
		EXPECT_STREQ( tString_asCStringT, pcszTestString );

		// to _bstr_t

		auto tString_as_bstr_t = Convert::To_bstr_t(tString);
		EXPECT_STREQ(static_cast<LPCWSTR>(tString_as_bstr_t), pcwszTestString);
	};

	fTestConvertToAllTargetTypes(straTest);
	fTestConvertToAllTargetTypes(strwTest);
	fTestConvertToAllTargetTypes(svaTest);
	fTestConvertToAllTargetTypes(svwTest);
	fTestConvertToAllTargetTypes(svzaTest);
	fTestConvertToAllTargetTypes(svzwTest);
	fTestConvertToAllTargetTypes(saTest);
	fTestConvertToAllTargetTypes(swTest);
	fTestConvertToAllTargetTypes(bsTest);
}

TEST(StringConversion, NonASCII)
{
	using namespace vlr::util;

	std::string saTest = "caractères ASCII";

	auto swValue = Convert::ToStdStringW_FromSystemDefaultASCII(saTest);
	//std::wcout << L"Test string (UTF16): " << swValue << std::endl;
	//for (auto cChar : swValue)
	//{
	//	std::wcout << std::hex << (unsigned short)cChar << L" ";
	//}
	//std::wcout << std::endl;

	// Note: Valid UTF16 encoding obtained (manually) via online resource
	// (https://www.browserling.com/tools/utf16-encode)
	std::vector<unsigned short> vecExpectedValue{ 0x63, 0x61, 0x72, 0x61, 0x63, 0x74, 0xe8, 0x72, 0x65, 0x73, 0x20, 0x41, 0x53, 0x43, 0x49, 0x49 };

	{
		size_t nExpectedValueIndex = 0;
		for (auto cChar : swValue)
		{
			ASSERT_LT(nExpectedValueIndex, vecExpectedValue.size());
			EXPECT_EQ(cChar, vecExpectedValue[nExpectedValueIndex++]);
		}
	}
}

TEST(StringConversion, ToFmtArg_String)
{
	using namespace vlr::util;

	constexpr auto pcaszTestString = "TestString";
	constexpr auto pcwszTestString = L"TestString";
	constexpr auto pcszTestString = _T("TestString");

	const auto straTest = std::string{ pcaszTestString };
	const auto strwTest = std::wstring{ pcwszTestString };
	const auto svaTest = std::string_view{ straTest };
	const auto svwTest = std::wstring_view{ strwTest };
	const auto svzaTest = vlr::zstring_view{ straTest };
	const auto svzwTest = vlr::wzstring_view{ strwTest };
	const auto saTest = CStringA{ pcaszTestString };
	const auto swTest = CStringW{ pcwszTestString };
	const auto bsTest = _bstr_t{ pcwszTestString };


	auto oStringCompare = vlr::StringCompare::CS();

	auto fTestConvertToAllTargetTypes = [&](const auto& tString)
	{
		// to std::string

		auto tFmtArg_asStdStringA = Convert::ToFmtArg_StringA(tString);
		EXPECT_TRUE(oStringCompare.AreEqual(tFmtArg_asStdStringA, pcaszTestString));
		auto tFmtArg_asStdStringW = Convert::ToFmtArg_StringW(tString);
		EXPECT_TRUE(oStringCompare.AreEqual(tFmtArg_asStdStringW, pcwszTestString));
		auto tFmtArg_asStdStringT = Convert::ToFmtArg_String(tString);
		EXPECT_TRUE(oStringCompare.AreEqual(tFmtArg_asStdStringT, pcszTestString));
	};

	fTestConvertToAllTargetTypes(straTest);
	fTestConvertToAllTargetTypes(strwTest);
	fTestConvertToAllTargetTypes(svaTest);
	fTestConvertToAllTargetTypes(svwTest);
	fTestConvertToAllTargetTypes(svzaTest);
	fTestConvertToAllTargetTypes(svzwTest);
	fTestConvertToAllTargetTypes(saTest);
	fTestConvertToAllTargetTypes(swTest);
	fTestConvertToAllTargetTypes(bsTest);

	// Check that constexpr conversions work as/where expected

	{
		constexpr auto svFmtArg_StringA = Convert::ToFmtArg_StringA(pcaszTestString);
	}
	{
		constexpr auto svFmtArg_StringW = Convert::ToFmtArg_StringW(pcwszTestString);
	}
	{
		constexpr auto svFmtArg_String = Convert::ToFmtArg_String(pcszTestString);
	}
	// This will not work: the std::string variables are not constexpr, and cannot be so before C++20
	//{
	//	constexpr auto svFmtArg_StringA = Convert::ToFmtArg_StringA(straTest);
	//}
	//{
	//	constexpr auto svFmtArg_StringW = Convert::ToFmtArg_StringW(strwTest);
	//}
	// These need to convert constexpr variables...
	{
		static constexpr auto svaTestVar = std::string_view{ "TestString" };
		constexpr auto svFmtArg_StringA = Convert::ToFmtArg_StringA(svaTestVar);
	}
	{
		static constexpr auto svwTestVar = std::wstring_view{ L"TestString" };
		constexpr auto svFmtArg_StringW = Convert::ToFmtArg_StringW(svwTestVar);
	}
	// These need to convert constexpr variables...
	{
		static constexpr auto svaTestVar = vlr::zstring_view{ "TestString" };
		constexpr auto svFmtArg_StringA = Convert::ToFmtArg_StringA(svaTestVar);
	}
	{
		static constexpr auto svwTestVar = vlr::wzstring_view{ L"TestString" };
		constexpr auto svFmtArg_StringW = Convert::ToFmtArg_StringW(svwTestVar);
	}
	// CString and _bstr_t are not constexpr compatible
}
