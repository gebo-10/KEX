#pragma once
#include "type.h"
namespace kengine
{
	class GUID
	{
	public:
		enum class FormatType
		{
			// 32 digits:
			// 00000000000000000000000000000000
			N,
			// 32 digits separated by hyphens:
			// 00000000-0000-0000-0000-000000000000
			D,
			// 32 digits separated by hyphens, enclosed in braces:
			// {00000000-0000-0000-0000-000000000000}
			B,
			// 32 digits separated by hyphens, enclosed in parentheses:
			// (00000000-0000-0000-0000-000000000000)
			P,
		};

		union
		{
			struct
			{
				// The first component
				uint32 A;
				// The second component
				uint32 B;
				// The third component
				uint32 C;
				// The fourth component
				uint32 D;
			};

			// Raw bytes with the GUID
			byte Raw[16];
			// Raw values with the GUID
			uint32 Values[4];
		};
	};
}