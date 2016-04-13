#Cellular Panels

##Code Structure
- Column layouts (i.e. `2col_40_60, 3col_33, 4col_25` etc.) are controlled by setting parameters
in *X*col_*XX*.inc and passing the values to the corresponding preprocess function
(@see `_include/preprocess.inc`), and a shared template (`_include/proto.tpl.inc`) is used to display
panels content.

- `layout_` layouts (i.e. `layout_inset_left, layout_inset_right, layout_stacked` etc.) are controlled
by setting parameters in *X*col_*XX*.inc and passing the values to the preprocess function in the same file.
A unique template (`_include/layout_NAME.tpl.inc`) is used to display panels content.

- Admin CSS is imported from `_include/admin.css`

