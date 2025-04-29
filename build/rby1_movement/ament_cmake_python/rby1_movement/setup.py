from setuptools import find_packages
from setuptools import setup

setup(
    name='rby1_movement',
    version='0.0.0',
    packages=find_packages(
        include=('rby1_movement', 'rby1_movement.*')),
)
