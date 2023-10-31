class Clause:
    premises: list = []
    conclusion: str = ''
    inferred: int = 0

    def __init__(self, premises, conclusion):
        self.premises = premises
        self.conclusion = conclusion
        self.inferred = len(premises)

def forward_chaining(clauses, query):
    inferred = set()
    new_symbols = True  # loop while we infer new stuff
    while new_symbols:
        new_symbols = False
        
        for clause in clauses:
            if len(clause.premises) == 0 and clause not in inferred:
                if clause.conclusion is query:
                    return True
                for s_clause in clauses:
                    if clause.conclusion in s_clause.premises:
                        s_clause.premises.remove(clause.conclusion)
                        clause.inferred -= 1
                        if clause.inferred <= 0 and clause not in inferred:
                            inferred.add(clause)
                            new_symbols = True
            
    return False

def main():
    clauses = [
            ([], 'fragile'),
            ([], 'falls down'),
            ([], 'contains liquid'),
            (['falls down', 'fragile'], 'breaks'),
            (['breaks', 'contains liquid'], 'makes a mess'),
            (['spoiled', 'breaks'], 'smells')
        ]

    query_1 = 'breaks'
    query_2 = 'makes a mess'
    query_3 = 'smells'

    clause_objects: list = []
    for clause in clauses:
        clause_objects.append(Clause(clause[0], clause[1]))

    print(f"Egg breaks: {forward_chaining(clause_objects, query_1)}")
    print(f"Egg makes a mess: {forward_chaining(clause_objects, query_2)}")
    print(f"Egg smells: {forward_chaining(clause_objects, query_3)}")

main()
