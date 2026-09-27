from csv import DictReader
from pathlib import Path
import yaml

class ImprovementDatabase(object):

    def __init__(self):
        with Path("tmp/improvement-database.yml").open() as f:
            db = yaml.safe_load(f)
            for entry in db:
                if not isinstance(entry['Address'], int):
                    raise Exception(entry)
        self.db = db
        with Path("tmp/bsim-openshc.tsv").open() as f:
            reader = DictReader(f, delimiter="\t")
            contents = [entry for entry in reader]
            for content in contents:
                if not isinstance(content["Location"], int):
                    content["Location"] = int(content["Location"], 16)
                if not isinstance(content["Matching_location"], int):
                    content["Matching_location"] = int(content["Matching_location"], 16)
        self.contents = contents

    def find_related_functions_by_address(self, addr: int):
        return [needle for needle in self.contents if addr == needle["Location"]]

    def find_related_functions_by_name(self, name):
        return [needle for needle in self.contents if name.lower() == needle["Function_name"].lower()]

    def find_related_functions_by_namespace(self, namespace):
        if not namespace.endswith("::"):
            namespace += "::"
        return [needle for needle in self.contents if needle["Function_name"].lower().startswith(namespace.lower())]

    def find_db_entries_by_address(self, addr: int):
        return [needle for needle in self.db if needle["Address"] == addr]

    def find_formatting_inspiration(self, name, truncate = 5):
        inspiration = []
        related = self.find_related_functions_by_name(name)
        for rel in related:
            addr: int = rel["Matching_location"] # type: ignore
            for entry in self.find_db_entries_by_address(addr):
                inspiration.append(yaml.safe_dump(entry))
        if not inspiration:
            namespace = "::".join(name.split("::")[:-1])
            related = self.find_related_functions_by_namespace(namespace)
            for rel in related:
                addr: int = rel["Matching_location"] # type: ignore
                for entry in self.find_db_entries_by_address(addr):
                    inspiration.append(yaml.safe_dump(entry))        
        return inspiration[:truncate]

