# from DataSource import DataSource
from Presenter import Presenter
from View import View
from weakref import ref


class Assembly:
    @classmethod
    def create_module(cls) -> View:
        presenter = Presenter()
        view = View(presenter=presenter)
        presenter.view = ref(view)()
        return view
