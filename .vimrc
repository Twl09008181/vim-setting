syntax enable
set nocompatible
colorscheme codedark

set nu
set laststatus=2
set clipboard=unnamed
set cursorline
set showcmd
set bg=dark  

hi  cursorline cterm=underline term=underline ctermfg=NONE ctermbg=NONE
"show status line fullpath"
let g:airline_section_b = '%F'

" search
set hlsearch
set incsearch
set ignorecase

" tab
set expandtab
set tabstop=2
set shiftwidth=2

" tabe
set showtabline=2


" filetype
filetype on
filetype indent on
filetype plugin on

" keymap

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

" if executable('clangd')
"       augroup lsp_clangd
"           autocmd!
"           autocmd User lsp_setup call lsp#register_server({
"                 \ 'name': 'clangd',
"                 \ 'cmd': {server_info->['clangd']},
"                 \ 'allowlist': ['.c','.cc', '.cpp', '.objc', '.objcpp']
"                 \ })
"           autocmd FileType c setlocal omnifunc=lsp#complete
"           autocmd FileType cpp setlocal omnifunc=lsp#complete
"           autocmd FileType objc setlocal omnifunc=lsp#complete
"           autocmd FileType objcpp setlocal omnifunc=lsp#complete
"           augroup end
" endif


inoremap <expr> <Tab>   pumvisible() ? "\<C-n>" : "\<Tab>"
inoremap <expr> <S-Tab> pumvisible() ? "\<C-p>" : "\<S-Tab>"


"LSP keymap

" return from CTRL-O (Older cusor position)
nnoremap \df :LspDefinition<cr>
nnoremap \tdf :tab split<cr>:LspDefinition<cr>
nnoremap \vdf :vsp<cr>:LspDefinition<cr>
nnoremap \sdf :sp<cr>:LspDefinition<cr>
nnoremap \dc :LspDeclaration<cr>
nnoremap \tdc :tab split<cr>:LspDeclaration<cr>
nnoremap \vdc :vsp<cr>:LspDeclaration<cr>
nnoremap \sdc :sp<cr>:LspDeclaration<cr>
nnoremap \r :LspReferences<cr>
nnoremap \hov :LspHover<cr>
nnoremap \adf :LspDocumentFormat<cr>
"document diagnostics"
nnoremap \dd :LspDocumentDiagnostic<cr>
nnoremap \nd :LspNextDiagnostic<cr>
nnoremap \pd :LspPreviousDiagnostic<cr>
" LspRename symbol
nnoremap \rn :LspRename<cr>
let g:markdown_fenced_languages = ['ts=typescript']



