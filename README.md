# templates

All the code necessary for my note taking workflow.
Create a latex beamer presentation or latex article from markdown notes with one shortcut.

Using ubuntu (still 14.10 ... ) and gedit.
I installed **pandoc**, **gedit-plugins** and **gedit-latex-plugin**.

The `gedit-markdown-beamer-shortcut.txt` is the script for an external tool.
It will create a latex beamer presentation from your markdown notes with one shortcut.

1. Open gedit > Tools > Manage External Tools ... > [+]
2. give it a name and a shortcut
3. make it language specific for markdown
4. paste the code inside the script window
~~~
#!/bin/sh
echo "$GEDIT_CURRENT_DOCUMENT_PATH"
filename="${GEDIT_CURRENT_DOCUMENT_PATH%.*}"
echo "$filename.pdf"
`pandoc -f markdown+tex_math_dollars+pipe_tables -t beamer $GEDIT_CURRENT_DOCUMENT_PATH -o $filename.pdf`
~~~

Same with [gedit-markdown-pdf-shortcut.txt](https://raw.githubusercontent.com/cipo7741/templates/master/shell/gedit-markdown-pdf-shortcut.txt) - just now it will create a latex article.
~~~
#!/bin/sh
echo "$GEDIT_CURRENT_DOCUMENT_PATH"
filename="${GEDIT_CURRENT_DOCUMENT_PATH%.*}"
echo "$filename.pdf"
`pandoc -V geometry:'top=1.5cm, bottom=1.5cm, left=2cm, right=1cm' $GEDIT_CURRENT_DOCUMENT_PATH -o $filename.pdf`
~~~

The [latex](https://github.com/cipo7741/templates/tree/master/latex) folder contains used latex scaffolds for presentations, bachelor thesis, assignments, ...
