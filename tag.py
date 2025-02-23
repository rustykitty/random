import sys
import re
from collections import Counter
from functools import reduce

data = sys.stdin.read()

c = Counter(match.group(1) for match in re.finditer(r'<ref +name="(.*?)">', data))

print(reduce(lambda x, y: x.replace(f'<ref name="{y}"', '<ref'), (i for i in c if c[i] > 1), data))