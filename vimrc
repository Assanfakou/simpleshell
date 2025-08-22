
set number
noremap mk :w<CR>:make<CR>
noremap mp :set makeprg=./build.sh<CR>
noremap mp :set makeprg=./build.sh<CR>

xnoremap gc dO/*<ESC>o*/<ESC>P
nnoremap gd ?/\*<CR>dd/\*\/<CR>dd

set showcmd
