operations = {
    # IMP Space: Stack manipulation
    "push": "  ",
    "dup": " \n ",
    "copy": " \t ",
    "swap": " \n\t",
    "pop": " \n\n",
    "slide": " \t\n",
    # IMP Tab Space: Arithmetic
    "add": "\t   ",
    "sub": "\t  \t",
    "mul": "\t  \n",
    "div": "\t \t ",
    "mod": "\t \t\t",
    # IMP tab tab: Heap access
    "store": "\t\t ",
    "load": "\t\t\t",
    # IMP LF: Flow control
    "label": "\n  ",
    "call": "\n \t",
    "jmp": "\n \n",
    "jz": "\n\t ",
    "jnz": "\n\t\t",
    "ret": "\n\t\n",
    "end": "\n\n\n",
    # IMP Tab LF: IO
    "outchr": "\t\n  ", # char
    "outnum": "\t\n \t", # number
    "inchr": "\t\n\t\n",
    "innum": "\t\n\t\t",
}