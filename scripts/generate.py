#!.env/bin/python
import argparse
import os
import re

HEADER_CODE = '''#ifndef __{0}_MAKER_H__
#define __{0}_MAKER_H__

#include <functional>
#include <memory>

#include "json/json-forwards.h"

#include "{1}/{1}.h"

namespace {1}
{{
  std::function<std::unique_ptr<{2}>(const Json::Value&)> get_{1}_maker(std::string);
}}

#endif
'''

SOURCE_CODE = '''#include "{0}_maker.h"

#include <unordered_map>

#include "json/json.h"

{1}

namespace {0}
{{
  static std::unordered_map<std::string, std::function<std::unique_ptr<{2}>(const Json::Value&)>> maker_map = {{{3}}};

  std::function<std::unique_ptr<{2}>(const Json::Value&)> get_{0}_maker(std::string key)
  {{
    return maker_map[key];
  }}
}}
'''

HDR_FILE = None
SRC_FILE = None
        
def write_files(name, includes, funcs):
    with open(HDR_FILE, 'w') as f:
        f.write(HEADER_CODE.format(name.upper(), name, name.title()))

    with open(SRC_FILE, 'w') as f:
        f.write(SOURCE_CODE.format(name, '\n'.join(includes), name.title(), ', '.join(funcs)))

def main(name, project_path):
    global HDR_FILE
    global SRC_FILE

    should_compile = False

    HDR_FILE = os.path.join(project_path, 'gen', 'include', '{}_maker.h'.format(name))
    SRC_FILE = os.path.join(project_path, 'gen', 'src', '{}_maker.cpp'.format(name))
    try:
        mtime = min(os.stat(HDR_FILE).st_mtime, os.stat(SRC_FILE).st_mtime)
    except:
        mtime = 0
    
    types = []
    for types_path, _, files in os.walk(os.path.join(project_path, 'src', name, 'types')):
        for f in files:
            m = re.search(r'(.*)\.cpp$', f)
            if m is None or m.lastindex != 1:
                continue
            types.append(m.group(1))

            type_hdr = os.path.join(project_path, 'include', m.group(1) + '.h')
            type_src = os.path.join(types_path, f)
            if os.stat(type_hdr).st_mtime >= mtime or os.stat(type_src).st_mtime >= mtime:
                should_compile = True
    types.sort()

    if should_compile is False:
        if not (os.path.exists(HDR_FILE) and os.path.exists(SRC_FILE)):
            write_files(name, [], [])
        return

    includes, funcs = [], []
    for t in types:
        includes.append('#include "{}.h"'.format(t))
        funcs.append('{{"{}", make_{}}}'.format(t, t))

    write_files(name, includes, funcs)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate "maker" source files.')
    parser.add_argument('name', type=str, choices=['enemy', 'prop'], help='Name of the "maker".')
    parser.add_argument('path', type=str, help='Project path.')
    args = parser.parse_args()
    main(args.name, args.path)
