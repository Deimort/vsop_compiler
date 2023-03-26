// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 53 "parser.y"

    
    #include "driver.hpp"

    using namespace std;

#line 53 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "parser.y"
namespace VSOP {
#line 146 "parser.tab.cc"

  /// Build a parser object.
  Parser::Parser (VSOP::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_INTEGER_LITERAL: // "integer-literal"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {

#line 588 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char Parser::yypact_ninf_ = -103;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -12,    -3,    14,   -12,  -103,     0,  -103,  -103,  -103,    19,
    -103,    -2,    37,  -103,    31,  -103,  -103,  -103,    13,    30,
      72,    65,    73,  -103,  -103,  -103,  -103,  -103,    55,    30,
      74,    13,  -103,    97,  -103,    30,  -103,    97,    64,    97,
    -103,    97,    97,    43,    46,    97,  -103,  -103,    97,  -103,
    -103,    38,  -103,   145,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,    84,    85,   156,  -103,   100,   190,
       6,   190,    86,  -103,    79,   131,    97,    97,  -103,    97,
      97,    97,    97,    97,    66,    97,    97,    97,    97,  -103,
    -103,    97,  -103,    97,    30,    97,   168,   113,  -103,    60,
      60,   201,   201,   179,   116,   206,   206,   206,  -103,  -103,
      98,    45,  -103,    97,  -103,    97,    97,    97,    97,  -103,
     119,  -103,    17,  -103,  -103,    97,  -103
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,    10,     0,
       5,     0,     0,     7,     0,     8,     9,     6,     0,     0,
       0,     0,    19,    16,    15,    17,    18,    14,     0,     0,
       0,     0,    11,     0,    21,     0,    20,     0,     0,     0,
      67,     0,     0,     0,     0,     0,    34,    66,     0,    63,
      64,    33,    38,     0,    25,    26,    27,    28,    29,    30,
      31,    32,    35,    65,     0,     0,    23,    36,     0,    49,
       0,    50,     0,    62,    48,     0,    41,     0,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      22,     0,    37,     0,     0,     0,    39,     0,    47,    54,
      55,    56,    57,    58,     0,    51,    52,    53,    59,    24,
      42,     0,    44,    41,    60,    41,     0,     0,     0,    40,
       0,    43,     0,    45,    61,     0,    46
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -103,  -103,  -103,   123,   120,  -103,  -103,  -103,   -28,   102,
    -103,    71,    48,   -33,  -102,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    10,    11,    15,    16,    28,    21,
      22,    52,    65,    96,    97,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63
  };

  const signed char
  Parser::yytable_[] =
  {
      53,    34,    13,     8,    66,    68,    69,    64,    70,    71,
       1,   119,    74,   120,     6,    75,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     9,    88,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    18,    88,    19,     5,
       8,    14,    93,    76,    98,   125,    99,   100,   101,   102,
     103,    23,   105,   106,   107,   108,    20,    77,    66,    24,
     110,    12,   112,    32,   117,    25,   111,    37,    26,    38,
      67,    30,    27,   118,    33,    39,    85,    86,    87,    29,
      88,    35,    31,   121,   122,   123,    72,    37,    73,    90,
      40,    41,   126,    94,    42,    43,    44,    45,    46,    88,
      37,    47,    38,    48,    49,    50,    92,    51,    39,   104,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   114,
      88,   115,   116,    40,    41,   124,     7,    42,    43,    44,
      45,    46,    17,    36,    47,    89,    48,    49,    50,   109,
      51,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,     0,    78,    95,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    91,    88,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     0,    88,   113,    79,    80,
      81,    82,    83,    84,    85,    86,    87,     0,    88,    79,
      80,    81,    82,    83,     0,    85,    86,    87,     0,    88,
      79,    80,    81,    82,     0,     0,    85,    86,    87,     0,
      88,    79,    80,     0,     0,     0,     0,    85,    86,    87,
       0,    88,    -1,    -1,    -1,     0,    88
  };

  const signed char
  Parser::yycheck_[] =
  {
      33,    29,     4,     3,    37,    38,    39,    35,    41,    42,
      22,   113,    45,   115,     0,    48,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    25,    20,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     5,    20,     7,    42,
       3,    43,    36,     5,    77,    28,    79,    80,    81,    82,
      83,    21,    85,    86,    87,    88,    43,    19,    91,    29,
      93,    42,    95,     8,    19,    35,    94,     3,    38,     5,
       6,     6,    42,    28,    19,    11,    16,    17,    18,     7,
      20,     7,     9,   116,   117,   118,    43,     3,    42,     4,
      26,    27,   125,     7,    30,    31,    32,    33,    34,    20,
       3,    37,     5,    39,    40,    41,     6,    43,    11,    43,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     6,
      20,     5,    24,    26,    27,     6,     3,    30,    31,    32,
      33,    34,    12,    31,    37,    64,    39,    40,    41,    91,
      43,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,     8,    23,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     8,    20,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    20,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    20,    10,
      11,    12,    13,    14,    -1,    16,    17,    18,    -1,    20,
      10,    11,    12,    13,    -1,    -1,    16,    17,    18,    -1,
      20,    10,    11,    -1,    -1,    -1,    -1,    16,    17,    18,
      -1,    20,    16,    17,    18,    -1,    20
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    22,    46,    47,    48,    42,     0,    48,     3,    25,
      49,    50,    42,     4,    43,    51,    52,    49,     5,     7,
      43,    54,    55,    21,    29,    35,    38,    42,    53,     7,
       6,     9,     8,    19,    53,     7,    54,     3,     5,    11,
      26,    27,    30,    31,    32,    33,    34,    37,    39,    40,
      41,    43,    56,    58,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    53,    57,    58,     6,    58,    58,
      58,    58,    43,    42,    58,    58,     5,    19,     8,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    20,    56,
       4,     8,     6,    36,     7,    23,    58,    59,    58,    58,
      58,    58,    58,    58,    43,    58,    58,    58,    58,    57,
      58,    53,    58,     9,     6,     5,    24,    19,    28,    59,
      59,    58,    58,    58,     6,    28,    58
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    48,    48,    49,    50,    50,
      50,    51,    51,    52,    53,    53,    53,    53,    53,    54,
      54,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    59,    60,    60,    61,    62,    62,    63,    64,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    68,    68,    68,    69,    69
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     3,     5,     3,     2,     2,
       0,     4,     6,     7,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     1,
       3,     0,     4,     6,     4,     6,     8,     3,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     6,     2,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"{\"", "\"}\"",
  "\"(\"", "\")\"", "\":\"", "\";\"", "\",\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"^\"", "\".\"", "\"=\"", "\"<\"", "\"<=\"", "\"<-\"",
  "\"and\"", "\"bool\"", "\"class\"", "\"do\"", "\"else\"", "\"extends\"",
  "\"false\"", "\"if\"", "\"in\"", "\"int32\"", "\"isnull\"", "\"let\"",
  "\"new\"", "\"not\"", "\"self\"", "\"string\"", "\"then\"", "\"true\"",
  "\"unit\"", "\"while\"", "\"integer-literal\"", "\"string-literal\"",
  "\"type-identifier\"", "\"object-identifier\"", "UNARYMINUS", "$accept",
  "program", "classList", "class", "classBody", "classBodyContent",
  "field", "method", "type", "formals", "formal", "block", "exprList",
  "expr", "args", "ifExpr", "whileExpr", "letExpr", "assignExpr",
  "unOpExpr", "binOpExpr", "callExpr", "newExpr", "literal",
  "boolean-literal", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   148,   148,   151,   152,   155,   156,   159,   162,   163,
     164,   167,   168,   171,   174,   175,   176,   177,   178,   181,
     182,   185,   188,   191,   192,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   211,
     212,   213,   218,   219,   222,   225,   226,   229,   232,   233,
     234,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     248,   249,   252,   255,   256,   257,   260,   261
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 19 "parser.y"
} // VSOP
#line 998 "parser.tab.cc"

#line 263 "parser.y"


void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
