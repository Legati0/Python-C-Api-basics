import os
from setuptools import setup, Extension

module = Extension('myModule', 	# name of your module
					sources=['mymodule.cpp'],	# all of your cpp src files
					include_dirs=['.'], 
					language='c++')

setup(name='myModule', # name of your module
	ext_modules = [module])