/**************************************************************************
 
  string_conversion.h
  =============================================================
  Project   : Tools for the CC manual writing task around cc_manual.sty.
  Function  : String conversion functions.
  System    : bison, flex, C++ (g++)
  Author    : (c) 1998 Lutz Kettner
  Revision  : $Revision$
  Date      : $Date$
 
**************************************************************************/

#ifndef STRING_CONVERSION_H
#define STRING_CONVERSION_H 1

#include <mstring.h>
#include <html_lex.h>

// New style conversion routines
// =======================================

string int_to_string( int i);

void remove_leading_spaces( string& s);
void remove_trailing_spaces( string& s);
void crop_string( string& s);
void compress_spaces_in_string( string& s);
void remove_separator( string& s);

void append_file_to_string( const string& name, string& s);

// Removes the quoted font changing commands used in CCMode: \I\, \B\ ...
string remove_font_commands( string name);

string basename_string( string name);  // basename without path and suffix
string path_string( string name);      // path with trailing / (maybe empty)
string remove_suffix( string name);    // remove '.' separated suffix


// Old style conversion routines
// =======================================

inline bool
is_html_multi_character( char c) {
    return c == SEPARATOR || c == '"' || c == '&' || c == '<' || c == '>';
}

const char* html_multi_character( char c);

void print_ascii_to_html( ostream& out, const char* txt);

void print_ascii_len_to_html( ostream& out, const char* txt, int n);

// This version eliminates multiple spaces.
void print_ascii_to_html_spc( ostream& out, const char* txt);
inline void print_ascii_to_html_spc( ostream& out, const string& txt) {
    print_ascii_to_html_spc( out, txt.c_str());
}

int strlen_ascii_to_html( const char* txt);

char* convert_ascii_to_html( const char* txt);

int strlen_fontified_ascii_to_html( const char* txt);

char* convert_fontified_ascii_to_html( const char* txt);
inline char* convert_fontified_ascii_to_html( const string& txt) {
    return convert_fontified_ascii_to_html( txt.c_str());
}

char* convert_C_to_html( const char* txt);
inline char* convert_C_to_html( const string& txt) {
    return convert_C_to_html( txt.c_str());
}


/* ================================================ */

// Filter decl. before writing to the index comment
void filter_for_index_comment( ostream& out, const char* text);
inline void filter_for_index_comment( ostream& out, const string& text) {
    filter_for_index_comment( out, text.c_str());
}
string filter_for_index_comment( string s);

// Filter characters that might not be allowed in hyperlink anchors.
void filter_for_index_anchor( ostream& out, const char* text);

/* An object storing the current font */
/* ================================== */
/* It is only used within CCMode at the moment */

enum Font { unknown_font = -1, 
	     rm_font, 
	     tt_font, 
	     bf_font, 
	     it_font, 
	     sl_font,
             sc_font,
             sf_font,
             var_font,
             math_font,
             end_font_array};

extern Font current_font;

const char* font_changing_tags( Font old_font, Font new_font);
const char* new_font_tags( Font new_font);
const char* lazy_new_font_tags( Font new_font);

/* The following is used to remember the font that was used in the */
/* previous column and to restore it in the next column. */
extern Font remember_font;  // default for program code.

inline const char* new_remember_font( Font new_font) {
    return new_font_tags( new_font);
}

const char* new_remember_font( char c);

inline const char* store_remember_font() {
    remember_font = current_font;
    return new_font_tags( it_font);
}
inline const char* get_remember_font() {
    return new_remember_font( remember_font);
}


#endif // STRING_CONVERSION_H 1 //
// EOF //

