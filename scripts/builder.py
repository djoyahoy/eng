#!.env/bin/python
import csv
import json
import os
import re
import yaml

class Loader(yaml.Loader):
    def __init__(self, stream):
        super().__init__(stream)
        self._root = os.path.split(stream.name)[0]

    def include(self, node):
        file_name = os.path.join(self._root, self.construct_scalar(node))
        with open(file_name, 'r') as f:
            return yaml.load(f, Loader)

    def transform(self, node):
        file_name = os.path.join(self._root, self.construct_scalar(node))
        with open(file_name, 'r') as f:
            reader = csv.reader(f)
            return [list(map(int, row)) for row in reader]

Loader.add_constructor('!include', Loader.include)
Loader.add_constructor('!transform', Loader.transform)

# TODO : right now only handles one stage and dungeon file
# TODO : should accept input and output dirs
def main():
    stages = ['../res/' + s for s in os.listdir('../res') if re.match(r'stage_.+', s)]
    for stage in stages:
        with open(os.path.join(stage, 'dungeon.yml')) as f:
            doc = yaml.load(f, Loader)

        with open('../build/res.json', 'w') as f:
            json.dump(doc['dungeon'], f)

if __name__ == '__main__':
    main()
