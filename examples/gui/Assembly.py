# from DataSource import DataSource
from Presenter import Presenter
from View import View
from weakref import ref


class Assembly:
    @classmethod
    def create_module(cls) -> View:
        # data_source = DataSource()
        presenter = Presenter()
        view = View(presenter=presenter)
        # data_source.view = ref(view)()
        presenter.view = ref(view)()
        return view
