#include <chrono>                  // for operator""s, chrono_literals
#include <iostream>                 // for cout, endl, ostream
#include <string>  // for allocator, char_traits, operator+, operator<<, string, to_string, basic_string
#include <thread>  // for sleep_for
#include <filesystem>
#include <ftxui/dom/elements.hpp>  // for text, gauge, operator|, flex, hbox, Element
#include <ftxui/screen/screen.hpp>  // for Screen
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui

#include "cpvg.h"

EXTERNC size_t cpvg(const char* src, size_t block_size, const char* dst)
{
	using namespace ftxui;
	using namespace std::chrono_literals;

	if(!std::filesystem::exists(src))
		return 0;
	size_t size = std::filesystem::file_size(src);

	FILE* ifp = fopen(src, "rb");
	FILE* ofp = fopen(dst, "w+b");
	void* buf = malloc(block_size);

	std::string reset_position;
	size_t transfered = 0;
	for (size_t res = 0; transfered < size; ) {
		const size_t len   = MIN(size - transfered, block_size);
		const size_t blk   = (len == block_size) ? block_size : 1;
		const size_t nmemb = (len == block_size) ? 1 : len;

		if((res = fread((unsigned char*)buf, blk, nmemb, ifp)) != nmemb)
			break;
		if((res = fwrite((unsigned char*)buf, blk, nmemb, ofp)) != nmemb)
			break;

		res = (len == block_size) ? block_size : res;

		transfered += res;
		std::string data_downloaded = std::to_string(transfered) + "/" + std::to_string(size);
		auto document = hbox({
				text("copying:"),
				gauge((float)transfered / (float)(size)) | flex,
				text(" " + data_downloaded),
				});
		auto screen = Screen(100, 1);
		Render(screen, document);
		std::cout << reset_position;
		screen.Print();
		reset_position = screen.ResetPosition();
		if(res < len)
			break;
	}

	std::cout << ((transfered == size) ? " Finished!" : " Failure!") << std::endl;

	fclose(ifp);
	fclose(ofp);
	free(buf);
	return transfered;
}
