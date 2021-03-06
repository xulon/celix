## Shell

The Celix Shell provides a service interface which can be used to interact with the Celix framework. Note that it does not offer a user interface. This modular approach enables having multiple frontends, e.g. textual or graphical.

While the shell can be extended with additional commands by other bundles, it already offers some built in commands:

    lb            list bundles
    install       install additional bundle
    uninstall     uninstall bundles
    update        update bundles

    start         start bundle
    stop          stop bundle

    help          displays available commands
    inspect       inspect service and components

    log           print log

Further information about a command can be retrieved by using `help` combined with the command.

###### CMake options
    BUILD_SHELL=ON
