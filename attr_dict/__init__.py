import functools 

class AttrDict(dict):
    """
    A dictionary that allows attribute access to keys.
    Inspired by JavaScript objects
    """

    @functools.wraps(dict.__init__)
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.__dict__ = self

    def __repr__(self):
        return f"{self.__class__.__name__}({super().__repr__()})"

    def __str__(self):
        return str(self.__dict__)

    def copy(self):
        return AttrDict(super().copy())
    
    def fromkeys(self, *args, **kwargs):
        return AttrDict(super().fromkeys(*args, **kwargs))
    
    def __copy__(self):
        return AttrDict(super().__copy__())
    
    def __deepcopy__(self, memo):
        return AttrDict(super().__deepcopy__(memo))