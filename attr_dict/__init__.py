from __future__ import annotations

import functools 

class AttrDict(dict):
    """
    A `dict` subclass that allows attribute access to keys.
    Inspired by JavaScript objects
    """

    @functools.wraps(dict.__init__)
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.__dict__ = self

    def __repr__(self):
        return f"{self.__class__.__name__}({super().__repr__()})"

    def __str__(self):
        return super().__repr__()

    @functools.wraps(dict.copy)
    def copy(self):
        return AttrDict(super().copy())

    @functools.wraps(dict.fromkeys)
    def fromkeys(self, *args, **kwargs):
        return AttrDict(super().fromkeys(*args, **kwargs))

    def __copy__(self):
        return AttrDict(super().__copy__())

    def __deepcopy__(self, memo):
        return AttrDict(super().__deepcopy__(memo))

    @classmethod
    def _typecheck(cls, other):
        return isinstance(other, dict) or isinstance(other, cls)

    def __or__(self, other: dict | AttrDict):
        if not self._typecheck(other): return NotImplemented
        res = AttrDict(self)
        res.update(other)
        return res

    def __ior__(self, other: dict | AttrDict):
        if not self._typecheck(other): return NotImplemented
        self.update(other)
        return self

    def __ror__(self, other: dict | AttrDict):
        if not self._typecheck(other): return NotImplemented
        res = AttrDict(other)
        res.update(self)
        return res
