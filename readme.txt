# my .vimrc setting 

## plug manager 
https://github.com/junegunn/vim-plug

## statusline 
https://github.com/vim-airline/vim-airline

## colorscheme 
https://github.com/tomasiser/vim-code-dark


## vim-lsp-clangd:

depedency:
1. https://github.com/prabirshrestha/vim-lsp
2. https://github.com/mattn/vim-lsp-settings

after PluginInstall, open any .cpp file and use LspInstallSever to install clangd.

Note:
in eda server(eda16), must care about:
libatomic.so.1 and libtinfo.so.5
using the soft link to generate this two libares and put them into ~/.local/share/vim-lsp-settings/servers/clangd/lib
```
ln -s /usr/lib64/libatomic_ops.so.1 libatomic.so.1    
ln -s /usr/lib64/libtinfo.so.6 libtinfo.so.5    
```

### generate compile_commands.json
compiledb:https://github.com/nickdiego/compiledb
```
$ compiledb make
```
example:
see EM
