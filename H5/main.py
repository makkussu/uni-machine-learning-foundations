def resolve(current: list, clause: list):
    data_set: set = set(current + clause)
    resolution: bool = False
    for_removal: str = ''

    print(data_set)
    for el in data_set:
        as_list: list = el.split('-')
        
        # Check that letter has negativity and ordinary letter
        # is present in the data set
        if (len(as_list) > 1 and as_list[1] in data_set) or f'-{as_list[0]}' in data_set:
            resolution = True
            for_removal = el
            break
    
    if resolution:
        if '-' in for_removal:
            data_set.remove(for_removal)
            data_set.remove(for_removal.split('-')[1])
            return [list(data_set)]
        
        data_set.remove(for_removal)
        data_set.remove(f'-{for_removal}')
        return [list(data_set)]
    
    return [current, clause]

def simple_resolution_solver(KB, neg_alpha):
    todo: list = [neg_alpha]
    done: list = KB.copy()
    while todo:
        current = todo.pop()
        
        for clause in done:
            resolvents = resolve(current, clause)
            print(f'Current: {current} / Clause: {clause} / Resolvents: {resolvents}')
            
            for resolvent in resolvents:
                if not resolvent:
                    return True
                if resolvent not in todo and resolvent not in done:
                    todo.append(resolvent)
        
        done.append(current)
    
    return False 

def main():
    exampleData: list = [['A', 'B', '-C', 'D']]
    exampleData2: list = [['A', 'B']]
    exampleData3: list = [['A', 'B', '-C']]
    exampleData4: list = [['A', '-B']]
    exampleData5: list = [['D']]
    
    query: list = ['A', 'C', '-D']
    query2: list = ['A', '-B']
    query3: list = ['A', 'C']
    query4: list = ['A', '-C', 'D']
    query5: list = ['-D']

    unicornData: list = [["-mythical", "immortal"], ["mythical", "mammal"], 
      ["-immortal", "horned"], ["-mammal", "horned"], ["-horned", "magical"]]
    
    unicornQuery: list = ['-magical']
    unicornQuery2: list = ['-mythical']
    unicornQuery3: list = ['-horned']

    eggData: list = [['fragile'], ['falls'], ['liquid'], ['-fragile', '-falls', 'breaks'], ['-breaks', '-liquid', 'mess'], ['-spoiled', '-breaks', 'smells']]

    eggQuery: list = ['-breaks']
    eggQuery2: list = ['=mess']
    eggQuery3: list = ['=smells']

    result: bool = simple_resolution_solver(unicornData, unicornQuery)
    print(result)

main()
    
