from setuptools import find_packages
from setuptools import setup

setup(
    name='pi_gpio_interface',
    version='0.0.1',
    packages=find_packages(
        include=('pi_gpio_interface', 'pi_gpio_interface.*')),
)
