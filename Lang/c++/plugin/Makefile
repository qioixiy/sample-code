all:
	g++ MyPlugin.cpp -fvisibility=hidden -shared -fPIC -o MyPlugin.dll
	g++ main.cpp PluginFactory.cpp -rdynamic -o main -ldl

clean:
	rm main *.dll -f