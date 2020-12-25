// 学学学

#include "ResourceLoader.h"

#include <boost/regex.hpp>
#include <iostream>
#include <string>

#include <boost/lambda/lambda.hpp>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>

#include "../Render/Texture.h"

namespace Resources
{
	void ResourceLoader::Load()
	{
        boost::filesystem::path p("D:\\STORAGE\\Projects\\TestOpenGL\\base\\textures");

        try
        {
            if (boost::filesystem::exists(p))
            {
                if (boost::filesystem::is_regular_file(p))
                    std::cout << p << " size is " << file_size(p) << '\n';

                else if (is_directory(p))
                {
                    std::cout << p << " is a directory containing:\n";

                    std::vector<boost::filesystem::path> v;

                    for (auto&& x : boost::filesystem::directory_iterator(p))
                    {
                        //auto&& ss = x;
                        auto s = x.path();
                        s = s.generic_string();
                        std::cout << "    " << s << '\n';
                        Render::Texture texture1(s.string().c_str());

                    }
                        //v.push_back(x.path());

                    //std::sort(v.begin(), v.end());

                    /*for (auto&& x : v)
                    {
                        std::cout << "    " << x.path() << '\n';
                    }*/
                        //Render::Texture texture1(x.string().c_str());
                }
                else
                    std::cout << p << " exists, but is not a regular file or directory\n";
            }
            else
                std::cout << p << " does not exist\n";
        }

        catch (const boost::filesystem::filesystem_error& ex)
        {
            std::cout << ex.what() << '\n';
        }
	}
}
