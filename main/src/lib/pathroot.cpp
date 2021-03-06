#include "pathroot.h"

#include <cstdlib>


/*
 * Copied and edited from http://qiita.com/hirotoshi/items/62b1de023e567ddeb984
 */
#ifdef _WIN32
#define ENV_HOME "USERPROFILE"
#else
#define ENV_HOME "HOME"
#endif



static const std::string getenv_limited(const char *name, const size_t size)
{
	if(!name || !getenv(name)) return std::string();
	std::string ret = getenv(name);
	if(size < ret.size()) { ret.erase(size); }
	return ret;
}

std::string path_root()
{
	std::string root_path = "";
	const std::string cache = getenv_limited("EX_CACHE", MAX_SAFE_PATH);
	root_path = cache.empty() ? "~/" : cache;
	
	if(root_path[root_path.length() - 1] != '/') { root_path += "/"; }
	
	if(root_path[0] == '~') {
		std::string home = getenv_limited(ENV_HOME, MAX_SAFE_PATH);
		root_path.replace(0, 1, home);
	}
	return root_path;
}
