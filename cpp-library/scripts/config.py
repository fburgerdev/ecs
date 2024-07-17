import json
from files import *

# Library
class Library:
    # constructor
    def __init__(self, data: any) -> None:
        # name
        self.name = data['name']
        # description
        self.description = data['description'] if 'description' in data else ''
        # type
        self.type = data['type'] if 'type' in data else 'static'
        # filename
        self.filename = data['filename'] if 'filename' in data else self.name
        # url
        self.url = data['url'] if 'url' in data else ''
# Test
class Test:
    # constructor
    def __init__(self, data: any, project_libraries: list[Library], project_defines: list[str]) -> None:
        # name
        self.name = data['name']
        # description
        self.description = data['description'] if 'description' in data else ''
        # files
        self.files = data['files']
        # defines
        self.defines :list[str] = project_defines.copy()
        if 'defines' in data:
            for define in data['defines']:
                if not define in self.defines:
                    self.defines.append(define)
        # libraries
        self.libraries :list[Library] = project_libraries.copy()
        if 'libraries' in data:
            for library in data['libraries']:
                if not library in self.libraries:
                    self.libraries.append(Library(library))
# Config
class Config:
    # constructor
    def __init__(self) -> None:
        data = json.load(open('cpp-library.json'))
        # project
        self.project = data['project']
        # description
        self.description = data['description'] if 'description' in data else ''
        # author
        self.author = ' '.join([word.capitalize() for word in data['author'].split(' ')]) if 'author' in data else 'Unknwon'
        # namespace
        self.namespace = data['namespace'] if 'namespace' in data else self.project
        # libraries
        self.libraries :list[Library]= []
        if 'libraries' in data:
            for library in data['libraries']:
                self.libraries.append(Library(library))
        # defines
        self.defines :list[str] = data['defines'] if 'defines' in data else []
        # test
        # :: tests
        self.tests :list[Test]= []
        if 'tests' in data:
            for test in data['tests']:
                self.tests.append(Test(test, self.libraries, self.defines))
        # :: default_test
        if 'default-test' in data:
            self.default_test = self.get_test(data['default-test'])
        elif len(self.tests) > 0:
            self.default_test = self.tests[0]
        else:
            self.default_test = None
    # get_test
    def get_test(self, name: str) -> Test:
        for test in self.tests:
            if test.name == name:
                return test
        if path.exists(f'tests/{name}.cpp'):
            return Test(json.loads(f'{{ "name": "{name}", "files": [ "{name}.cpp" ]}}'), self.libraries, self.defines)
        raise Exception(f'Test {name} not found')
# global
config = Config()