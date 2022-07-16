syntax enable
set nocompatible
colorscheme codedark

set nu
set laststatus=2
set clipboard=unnamed
set cursorline
set showcmd
set bg=dark  
hi LineNr cterm=bold ctermfg=DarkGrey ctermbg=NONE
hi CursorLineNr cterm=bold ctermfg=Green ctermbg=NONE"

"show status line fullpath"
let g:airline_section_b = '%F'
let g:airline#extensions#tabline#enabled = 1

" search
set hlsearch
set incsearch
set ignorecase
set smartcase

" tab
set expandtab
set tabstop=4
set shiftwidth=2

" tabe
set showtabline=2


" filetype
filetype on
filetype indent on
filetype plugin on

" keymap
map jj <ESC>
inoremap ( ()<left>
inoremap [ []<left>
inoremap {{ {}<left>
"{ and enter (<CR> == enter)"
inoremap {<CR> {<CR>}<Esc>ko




call plug#begin()
Plug 'preservim/NERDTree'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'prabirshrestha/asyncomplete.vim'
Plug 'prabirshrestha/vim-lsp'
Plug 'prabirshrestha/asyncomplete-lsp.vim'
Plug 'mattn/vim-lsp-settings'
call plug#end()

if executable('clangd')
      augroup lsp_clangd
          autocmd!
          autocmd User lsp_setup call lsp#register_server({
                \ 'name': 'clangd',
                \ 'cmd': {server_info->['clangd']},
                \ 'whitelist': ['c', 'cpp', 'objc', 'objcpp'],
                \ })
          autocmd FileType c setlocal omnifunc=lsp#complete
          autocmd FileType cpp setlocal omnifunc=lsp#complete
          autocmd FileType objc setlocal omnifunc=lsp#complete
          autocmd FileType objcpp setlocal omnifunc=lsp#complete
          augroup end
endif
