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





#include "parser.hpp"


// Unqualified %code blocks.
#line 54 "parser.y"

    #include "driver.hpp"
    using namespace std;

#line 51 "parser.cpp"


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
#line 144 "parser.cpp"

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

      case symbol_kind::S_assignExpr: // assignExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<AssignNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binOpExpr: // binOpExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<BinOpNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< std::shared_ptr<BlockNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_callExpr: // callExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<CallNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classBody: // classBody
      case symbol_kind::S_classBodyContent: // classBodyContent
        value.YY_MOVE_OR_COPY< std::shared_ptr<ClassBodyNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.YY_MOVE_OR_COPY< std::shared_ptr<ClassNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< std::shared_ptr<ExprNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< std::shared_ptr<FieldNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< std::shared_ptr<FormalNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifExpr: // ifExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<IfNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_letExpr: // letExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<LetNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_booleanLiteral: // booleanLiteral
        value.YY_MOVE_OR_COPY< std::shared_ptr<LiteralNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< std::shared_ptr<MethodNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_newExpr: // newExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<NewNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unOpExpr: // unOpExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<UnOpNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileExpr: // whileExpr
        value.YY_MOVE_OR_COPY< std::shared_ptr<WhileNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_classList: // classList
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<ClassNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exprList: // exprList
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<ExprNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<FormalNode>> > (YY_MOVE (that.value));
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

      case symbol_kind::S_assignExpr: // assignExpr
        value.move< std::shared_ptr<AssignNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_binOpExpr: // binOpExpr
        value.move< std::shared_ptr<BinOpNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< std::shared_ptr<BlockNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_callExpr: // callExpr
        value.move< std::shared_ptr<CallNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classBody: // classBody
      case symbol_kind::S_classBodyContent: // classBodyContent
        value.move< std::shared_ptr<ClassBodyNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.move< std::shared_ptr<ClassNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< std::shared_ptr<ExprNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< std::shared_ptr<FieldNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< std::shared_ptr<FormalNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifExpr: // ifExpr
        value.move< std::shared_ptr<IfNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_letExpr: // letExpr
        value.move< std::shared_ptr<LetNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_booleanLiteral: // booleanLiteral
        value.move< std::shared_ptr<LiteralNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< std::shared_ptr<MethodNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_newExpr: // newExpr
        value.move< std::shared_ptr<NewNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unOpExpr: // unOpExpr
        value.move< std::shared_ptr<UnOpNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileExpr: // whileExpr
        value.move< std::shared_ptr<WhileNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
      case symbol_kind::S_type: // type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_classList: // classList
        value.move< std::vector<std::shared_ptr<ClassNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exprList: // exprList
      case symbol_kind::S_args: // args
        value.move< std::vector<std::shared_ptr<ExprNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<std::shared_ptr<FormalNode>> > (YY_MOVE (that.value));
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

      case symbol_kind::S_assignExpr: // assignExpr
        value.copy< std::shared_ptr<AssignNode> > (that.value);
        break;

      case symbol_kind::S_binOpExpr: // binOpExpr
        value.copy< std::shared_ptr<BinOpNode> > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< std::shared_ptr<BlockNode> > (that.value);
        break;

      case symbol_kind::S_callExpr: // callExpr
        value.copy< std::shared_ptr<CallNode> > (that.value);
        break;

      case symbol_kind::S_classBody: // classBody
      case symbol_kind::S_classBodyContent: // classBodyContent
        value.copy< std::shared_ptr<ClassBodyNode> > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.copy< std::shared_ptr<ClassNode> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< std::shared_ptr<ExprNode> > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< std::shared_ptr<FieldNode> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< std::shared_ptr<FormalNode> > (that.value);
        break;

      case symbol_kind::S_ifExpr: // ifExpr
        value.copy< std::shared_ptr<IfNode> > (that.value);
        break;

      case symbol_kind::S_letExpr: // letExpr
        value.copy< std::shared_ptr<LetNode> > (that.value);
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_booleanLiteral: // booleanLiteral
        value.copy< std::shared_ptr<LiteralNode> > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< std::shared_ptr<MethodNode> > (that.value);
        break;

      case symbol_kind::S_newExpr: // newExpr
        value.copy< std::shared_ptr<NewNode> > (that.value);
        break;

      case symbol_kind::S_unOpExpr: // unOpExpr
        value.copy< std::shared_ptr<UnOpNode> > (that.value);
        break;

      case symbol_kind::S_whileExpr: // whileExpr
        value.copy< std::shared_ptr<WhileNode> > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
      case symbol_kind::S_type: // type
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_classList: // classList
        value.copy< std::vector<std::shared_ptr<ClassNode>> > (that.value);
        break;

      case symbol_kind::S_exprList: // exprList
      case symbol_kind::S_args: // args
        value.copy< std::vector<std::shared_ptr<ExprNode>> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.copy< std::vector<std::shared_ptr<FormalNode>> > (that.value);
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

      case symbol_kind::S_assignExpr: // assignExpr
        value.move< std::shared_ptr<AssignNode> > (that.value);
        break;

      case symbol_kind::S_binOpExpr: // binOpExpr
        value.move< std::shared_ptr<BinOpNode> > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< std::shared_ptr<BlockNode> > (that.value);
        break;

      case symbol_kind::S_callExpr: // callExpr
        value.move< std::shared_ptr<CallNode> > (that.value);
        break;

      case symbol_kind::S_classBody: // classBody
      case symbol_kind::S_classBodyContent: // classBodyContent
        value.move< std::shared_ptr<ClassBodyNode> > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.move< std::shared_ptr<ClassNode> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< std::shared_ptr<ExprNode> > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< std::shared_ptr<FieldNode> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< std::shared_ptr<FormalNode> > (that.value);
        break;

      case symbol_kind::S_ifExpr: // ifExpr
        value.move< std::shared_ptr<IfNode> > (that.value);
        break;

      case symbol_kind::S_letExpr: // letExpr
        value.move< std::shared_ptr<LetNode> > (that.value);
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_booleanLiteral: // booleanLiteral
        value.move< std::shared_ptr<LiteralNode> > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< std::shared_ptr<MethodNode> > (that.value);
        break;

      case symbol_kind::S_newExpr: // newExpr
        value.move< std::shared_ptr<NewNode> > (that.value);
        break;

      case symbol_kind::S_unOpExpr: // unOpExpr
        value.move< std::shared_ptr<UnOpNode> > (that.value);
        break;

      case symbol_kind::S_whileExpr: // whileExpr
        value.move< std::shared_ptr<WhileNode> > (that.value);
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
      case symbol_kind::S_type: // type
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_classList: // classList
        value.move< std::vector<std::shared_ptr<ClassNode>> > (that.value);
        break;

      case symbol_kind::S_exprList: // exprList
      case symbol_kind::S_args: // args
        value.move< std::vector<std::shared_ptr<ExprNode>> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::vector<std::shared_ptr<FormalNode>> > (that.value);
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

      case symbol_kind::S_assignExpr: // assignExpr
        yylhs.value.emplace< std::shared_ptr<AssignNode> > ();
        break;

      case symbol_kind::S_binOpExpr: // binOpExpr
        yylhs.value.emplace< std::shared_ptr<BinOpNode> > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< std::shared_ptr<BlockNode> > ();
        break;

      case symbol_kind::S_callExpr: // callExpr
        yylhs.value.emplace< std::shared_ptr<CallNode> > ();
        break;

      case symbol_kind::S_classBody: // classBody
      case symbol_kind::S_classBodyContent: // classBodyContent
        yylhs.value.emplace< std::shared_ptr<ClassBodyNode> > ();
        break;

      case symbol_kind::S_class: // class
        yylhs.value.emplace< std::shared_ptr<ClassNode> > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< std::shared_ptr<ExprNode> > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< std::shared_ptr<FieldNode> > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< std::shared_ptr<FormalNode> > ();
        break;

      case symbol_kind::S_ifExpr: // ifExpr
        yylhs.value.emplace< std::shared_ptr<IfNode> > ();
        break;

      case symbol_kind::S_letExpr: // letExpr
        yylhs.value.emplace< std::shared_ptr<LetNode> > ();
        break;

      case symbol_kind::S_literal: // literal
      case symbol_kind::S_booleanLiteral: // booleanLiteral
        yylhs.value.emplace< std::shared_ptr<LiteralNode> > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< std::shared_ptr<MethodNode> > ();
        break;

      case symbol_kind::S_newExpr: // newExpr
        yylhs.value.emplace< std::shared_ptr<NewNode> > ();
        break;

      case symbol_kind::S_unOpExpr: // unOpExpr
        yylhs.value.emplace< std::shared_ptr<UnOpNode> > ();
        break;

      case symbol_kind::S_whileExpr: // whileExpr
        yylhs.value.emplace< std::shared_ptr<WhileNode> > ();
        break;

      case symbol_kind::S_STRING_LITERAL: // "string-literal"
      case symbol_kind::S_TYPE_IDENTIFIER: // "type-identifier"
      case symbol_kind::S_OBJECT_IDENTIFIER: // "object-identifier"
      case symbol_kind::S_type: // type
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_classList: // classList
        yylhs.value.emplace< std::vector<std::shared_ptr<ClassNode>> > ();
        break;

      case symbol_kind::S_exprList: // exprList
      case symbol_kind::S_args: // args
        yylhs.value.emplace< std::vector<std::shared_ptr<ExprNode>> > ();
        break;

      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< std::vector<std::shared_ptr<FormalNode>> > ();
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
  case 2: // program: classList
#line 150 "parser.y"
                   { yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<ClassNode>> > (); driver.setProgram(yylhs.location, yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > ()); driver.result = 0; }
#line 993 "parser.cpp"
    break;

  case 3: // classList: class
#line 153 "parser.y"
          { yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > () = std::vector<std::shared_ptr<ClassNode>>(); yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > ().push_back(yystack_[0].value.as < std::shared_ptr<ClassNode> > ()); }
#line 999 "parser.cpp"
    break;

  case 4: // classList: classList class
#line 154 "parser.y"
                      { yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > () = yystack_[1].value.as < std::vector<std::shared_ptr<ClassNode>> > (); yylhs.value.as < std::vector<std::shared_ptr<ClassNode>> > ().push_back(yystack_[0].value.as < std::shared_ptr<ClassNode> > ()); }
#line 1005 "parser.cpp"
    break;

  case 5: // class: "class" "type-identifier" classBody
#line 157 "parser.y"
                                    { yylhs.value.as < std::shared_ptr<ClassNode> > () = std::make_shared<ClassNode>(yystack_[2].location, yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<ClassBodyNode> > ()); }
#line 1011 "parser.cpp"
    break;

  case 6: // class: "class" "type-identifier" "extends" "type-identifier" classBody
#line 158 "parser.y"
                                                              { yylhs.value.as < std::shared_ptr<ClassNode> > () = std::make_shared<ClassNode>(yystack_[4].location, yystack_[3].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<ClassBodyNode> > (), yystack_[1].value.as < std::string > ()); }
#line 1017 "parser.cpp"
    break;

  case 7: // classBody: "{" classBodyContent "}"
#line 161 "parser.y"
                                   { yylhs.value.as < std::shared_ptr<ClassBodyNode> > () = yystack_[1].value.as < std::shared_ptr<ClassBodyNode> > (); }
#line 1023 "parser.cpp"
    break;

  case 8: // classBodyContent: classBodyContent field
#line 164 "parser.y"
                           { yylhs.value.as < std::shared_ptr<ClassBodyNode> > () = yystack_[1].value.as < std::shared_ptr<ClassBodyNode> > (); yylhs.value.as < std::shared_ptr<ClassBodyNode> > ()->addField(yystack_[0].value.as < std::shared_ptr<FieldNode> > ()); }
#line 1029 "parser.cpp"
    break;

  case 9: // classBodyContent: classBodyContent method
#line 165 "parser.y"
                              { yylhs.value.as < std::shared_ptr<ClassBodyNode> > () = yystack_[1].value.as < std::shared_ptr<ClassBodyNode> > (); yylhs.value.as < std::shared_ptr<ClassBodyNode> > ()->addMethod(yystack_[0].value.as < std::shared_ptr<MethodNode> > ()); }
#line 1035 "parser.cpp"
    break;

  case 10: // classBodyContent: %empty
#line 166 "parser.y"
             { yylhs.value.as < std::shared_ptr<ClassBodyNode> > () = std::make_shared<ClassBodyNode>(yylhs.location); }
#line 1041 "parser.cpp"
    break;

  case 11: // field: "object-identifier" ":" type ";"
#line 169 "parser.y"
                                           { yylhs.value.as < std::shared_ptr<FieldNode> > () = std::make_shared<FieldNode>(yystack_[3].location, yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::string > ()); }
#line 1047 "parser.cpp"
    break;

  case 12: // field: "object-identifier" ":" type "<-" expr ";"
#line 170 "parser.y"
                                                         { yylhs.value.as < std::shared_ptr<FieldNode> > () = std::make_shared<FieldNode>(yystack_[5].location, yystack_[5].value.as < std::string > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1053 "parser.cpp"
    break;

  case 13: // method: "object-identifier" "(" formals ")" ":" type block
#line 173 "parser.y"
                                                         { yylhs.value.as < std::shared_ptr<MethodNode> > () = std::make_shared<MethodNode>(yystack_[6].location, yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::vector<std::shared_ptr<FormalNode>> > (), yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<BlockNode> > ()); }
#line 1059 "parser.cpp"
    break;

  case 14: // type: "type-identifier"
#line 176 "parser.y"
                    { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1065 "parser.cpp"
    break;

  case 15: // type: "int32"
#line 177 "parser.y"
            { yylhs.value.as < std::string > () = "int32"; }
#line 1071 "parser.cpp"
    break;

  case 16: // type: "bool"
#line 178 "parser.y"
           { yylhs.value.as < std::string > () = "bool"; }
#line 1077 "parser.cpp"
    break;

  case 17: // type: "string"
#line 179 "parser.y"
             { yylhs.value.as < std::string > () = "string"; }
#line 1083 "parser.cpp"
    break;

  case 18: // type: "unit"
#line 180 "parser.y"
           { yylhs.value.as < std::string > () = "unit"; }
#line 1089 "parser.cpp"
    break;

  case 19: // formals: formal "," formals
#line 183 "parser.y"
                         { yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<FormalNode>> > (); yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > ().insert(yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > ().begin(), yystack_[2].value.as < std::shared_ptr<FormalNode> > ()); }
#line 1095 "parser.cpp"
    break;

  case 20: // formals: formal
#line 184 "parser.y"
             { yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > () = std::vector<std::shared_ptr<FormalNode>>(); yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > ().push_back(yystack_[0].value.as < std::shared_ptr<FormalNode> > ()); }
#line 1101 "parser.cpp"
    break;

  case 21: // formals: %empty
#line 185 "parser.y"
             { yylhs.value.as < std::vector<std::shared_ptr<FormalNode>> > () = std::vector<std::shared_ptr<FormalNode>>(); }
#line 1107 "parser.cpp"
    break;

  case 22: // formal: "object-identifier" ":" type
#line 188 "parser.y"
                                 { yylhs.value.as < std::shared_ptr<FormalNode> > () = std::make_shared<FormalNode>(yystack_[2].location, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ()); }
#line 1113 "parser.cpp"
    break;

  case 23: // block: "{" exprList "}"
#line 191 "parser.y"
                           { yylhs.value.as < std::shared_ptr<BlockNode> > () = std::make_shared<BlockNode>(yystack_[2].location, yystack_[1].value.as < std::vector<std::shared_ptr<ExprNode>> > ()); }
#line 1119 "parser.cpp"
    break;

  case 24: // exprList: expr
#line 194 "parser.y"
         { yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > () = std::vector<std::shared_ptr<ExprNode>>(); yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().push_back(yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1125 "parser.cpp"
    break;

  case 25: // exprList: expr ";" exprList
#line 195 "parser.y"
                              { yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<ExprNode>> > (); yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().insert(yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().begin(), yystack_[2].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1131 "parser.cpp"
    break;

  case 26: // expr: ifExpr
#line 198 "parser.y"
           { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<IfNode> > ();}
#line 1137 "parser.cpp"
    break;

  case 27: // expr: whileExpr
#line 199 "parser.y"
                { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<WhileNode> > (); }
#line 1143 "parser.cpp"
    break;

  case 28: // expr: letExpr
#line 200 "parser.y"
              { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<LetNode> > ();}
#line 1149 "parser.cpp"
    break;

  case 29: // expr: assignExpr
#line 201 "parser.y"
                 { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<AssignNode> > ();}
#line 1155 "parser.cpp"
    break;

  case 30: // expr: unOpExpr
#line 202 "parser.y"
               { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<UnOpNode> > ();}
#line 1161 "parser.cpp"
    break;

  case 31: // expr: binOpExpr
#line 203 "parser.y"
                { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<BinOpNode> > ();}
#line 1167 "parser.cpp"
    break;

  case 32: // expr: callExpr
#line 204 "parser.y"
               { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<CallNode> > ();}
#line 1173 "parser.cpp"
    break;

  case 33: // expr: newExpr
#line 205 "parser.y"
              { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<NewNode> > ();}
#line 1179 "parser.cpp"
    break;

  case 34: // expr: "object-identifier"
#line 206 "parser.y"
                        { yylhs.value.as < std::shared_ptr<ExprNode> > () = std::make_shared<IdentifierNode>(yystack_[0].location, yystack_[0].value.as < std::string > ()); }
#line 1185 "parser.cpp"
    break;

  case 35: // expr: "self"
#line 207 "parser.y"
           { yylhs.value.as < std::shared_ptr<ExprNode> > () = std::make_shared<SelfNode>(yystack_[0].location); }
#line 1191 "parser.cpp"
    break;

  case 36: // expr: literal
#line 208 "parser.y"
              { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<LiteralNode> > (); }
#line 1197 "parser.cpp"
    break;

  case 37: // expr: "(" ")"
#line 209 "parser.y"
                { yylhs.value.as < std::shared_ptr<ExprNode> > () = std::make_shared<UnitNode>(yystack_[1].location); }
#line 1203 "parser.cpp"
    break;

  case 38: // expr: "(" expr ")"
#line 210 "parser.y"
                     { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[1].value.as < std::shared_ptr<ExprNode> > (); }
#line 1209 "parser.cpp"
    break;

  case 39: // expr: block
#line 211 "parser.y"
            { yylhs.value.as < std::shared_ptr<ExprNode> > () = yystack_[0].value.as < std::shared_ptr<BlockNode> > (); }
#line 1215 "parser.cpp"
    break;

  case 40: // args: expr
#line 214 "parser.y"
         { yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > () = std::vector<std::shared_ptr<ExprNode>>(); yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().push_back(yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1221 "parser.cpp"
    break;

  case 41: // args: expr "," args
#line 215 "parser.y"
                      { yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > () = yystack_[0].value.as < std::vector<std::shared_ptr<ExprNode>> > (); yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().insert(yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > ().begin(), yystack_[2].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1227 "parser.cpp"
    break;

  case 42: // args: %empty
#line 216 "parser.y"
             { yylhs.value.as < std::vector<std::shared_ptr<ExprNode>> > () = std::vector<std::shared_ptr<ExprNode>>(); }
#line 1233 "parser.cpp"
    break;

  case 43: // ifExpr: "if" expr "then" expr
#line 219 "parser.y"
                      { yylhs.value.as < std::shared_ptr<IfNode> > () = std::make_shared<IfNode>(yystack_[3].location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1239 "parser.cpp"
    break;

  case 44: // ifExpr: "if" expr "then" expr "else" expr
#line 220 "parser.y"
                                  { yylhs.value.as < std::shared_ptr<IfNode> > () = std::make_shared<IfNode>(yystack_[5].location, yystack_[4].value.as < std::shared_ptr<ExprNode> > (), yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1245 "parser.cpp"
    break;

  case 45: // whileExpr: "while" expr "do" expr
#line 223 "parser.y"
                       { yylhs.value.as < std::shared_ptr<WhileNode> > () = std::make_shared<WhileNode>(yystack_[3].location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1251 "parser.cpp"
    break;

  case 46: // letExpr: "let" "object-identifier" ":" type "in" expr
#line 226 "parser.y"
                                             { yylhs.value.as < std::shared_ptr<LetNode> > () = std::make_shared<LetNode>(yystack_[5].location, yystack_[4].value.as < std::string > (), yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1257 "parser.cpp"
    break;

  case 47: // letExpr: "let" "object-identifier" ":" type "<-" expr "in" expr
#line 227 "parser.y"
                                                           { yylhs.value.as < std::shared_ptr<LetNode> > () = std::make_shared<LetNode>(yystack_[7].location, yystack_[6].value.as < std::string > (), yystack_[4].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > (), yystack_[2].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1263 "parser.cpp"
    break;

  case 48: // assignExpr: "object-identifier" "<-" expr
#line 230 "parser.y"
                                  { yylhs.value.as < std::shared_ptr<AssignNode> > () = std::make_shared<AssignNode>(yystack_[2].location, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1269 "parser.cpp"
    break;

  case 49: // unOpExpr: "not" expr
#line 233 "parser.y"
             { yylhs.value.as < std::shared_ptr<UnOpNode> > () = std::make_shared<NotUnOpNode>(yystack_[1].location, yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1275 "parser.cpp"
    break;

  case 50: // unOpExpr: "-" expr
#line 234 "parser.y"
                                  { yylhs.value.as < std::shared_ptr<UnOpNode> > () = std::make_shared<MinusUnOpNode>(yystack_[1].location, yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1281 "parser.cpp"
    break;

  case 51: // unOpExpr: "isnull" expr
#line 235 "parser.y"
                  { yylhs.value.as < std::shared_ptr<UnOpNode> > () = std::make_shared<IsnullUnOpNode>(yystack_[1].location, yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1287 "parser.cpp"
    break;

  case 52: // binOpExpr: expr "=" expr
#line 238 "parser.y"
                    { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<EqualBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1293 "parser.cpp"
    break;

  case 53: // binOpExpr: expr "<" expr
#line 239 "parser.y"
                      { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<LowerBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1299 "parser.cpp"
    break;

  case 54: // binOpExpr: expr "<=" expr
#line 240 "parser.y"
                            { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<LowerOrEqualBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1305 "parser.cpp"
    break;

  case 55: // binOpExpr: expr "+" expr
#line 241 "parser.y"
                     { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<AddBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1311 "parser.cpp"
    break;

  case 56: // binOpExpr: expr "-" expr
#line 242 "parser.y"
                      { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<MinusBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1317 "parser.cpp"
    break;

  case 57: // binOpExpr: expr "*" expr
#line 243 "parser.y"
                      { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<MulBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1323 "parser.cpp"
    break;

  case 58: // binOpExpr: expr "/" expr
#line 244 "parser.y"
                    { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<DivBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1329 "parser.cpp"
    break;

  case 59: // binOpExpr: expr "^" expr
#line 245 "parser.y"
                    { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<PowBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1335 "parser.cpp"
    break;

  case 60: // binOpExpr: expr "and" expr
#line 246 "parser.y"
                    { yylhs.value.as < std::shared_ptr<BinOpNode> > () = std::make_shared<AndBinOpNode>(yylhs.location, yystack_[2].value.as < std::shared_ptr<ExprNode> > (), yystack_[0].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1341 "parser.cpp"
    break;

  case 61: // callExpr: "object-identifier" "(" args ")"
#line 249 "parser.y"
                                     { yylhs.value.as < std::shared_ptr<CallNode> > () = std::make_shared<CallNode>(yystack_[3].location, yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<std::shared_ptr<ExprNode>> > ()); }
#line 1347 "parser.cpp"
    break;

  case 62: // callExpr: expr "." "object-identifier" "(" args ")"
#line 250 "parser.y"
                                                { yylhs.value.as < std::shared_ptr<CallNode> > () = std::make_shared<CallNode>(yystack_[5].location, yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<std::shared_ptr<ExprNode>> > (), yystack_[5].value.as < std::shared_ptr<ExprNode> > ()); }
#line 1353 "parser.cpp"
    break;

  case 63: // newExpr: "new" "type-identifier"
#line 253 "parser.y"
                        { yylhs.value.as < std::shared_ptr<NewNode> > () = std::make_shared<NewNode>(yystack_[1].location, yystack_[0].value.as < std::string > ());}
#line 1359 "parser.cpp"
    break;

  case 64: // literal: "integer-literal"
#line 256 "parser.y"
                    { yylhs.value.as < std::shared_ptr<LiteralNode> > () = std::make_shared<LiteralNode>(yystack_[0].location, std::to_string(yystack_[0].value.as < int > ()), "int32"); }
#line 1365 "parser.cpp"
    break;

  case 65: // literal: "string-literal"
#line 257 "parser.y"
                     { yylhs.value.as < std::shared_ptr<LiteralNode> > () = std::make_shared<LiteralNode>(yystack_[0].location, yystack_[0].value.as < std::string > (), "string"); }
#line 1371 "parser.cpp"
    break;

  case 66: // literal: booleanLiteral
#line 258 "parser.y"
                     { yylhs.value.as < std::shared_ptr<LiteralNode> > () = yystack_[0].value.as < std::shared_ptr<LiteralNode> > (); }
#line 1377 "parser.cpp"
    break;

  case 67: // booleanLiteral: "true"
#line 261 "parser.y"
         { yylhs.value.as < std::shared_ptr<LiteralNode> > () = std::make_shared<LiteralNode>(yystack_[0].location, "true", "bool"); }
#line 1383 "parser.cpp"
    break;

  case 68: // booleanLiteral: "false"
#line 262 "parser.y"
            { yylhs.value.as < std::shared_ptr<LiteralNode> > () = std::make_shared<LiteralNode>(yystack_[0].location, "false", "bool"); }
#line 1389 "parser.cpp"
    break;


#line 1393 "parser.cpp"

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
     -12,    14,    61,   -12,  -103,     0,  -103,  -103,  -103,    29,
    -103,    -2,    11,  -103,    31,  -103,  -103,  -103,    33,    30,
      74,    76,    77,  -103,  -103,  -103,  -103,  -103,    55,    30,
      80,    33,  -103,    97,  -103,    30,  -103,    97,    64,    97,
    -103,    97,    97,    46,    51,    97,  -103,  -103,    97,  -103,
    -103,    38,  -103,   160,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,    85,    95,   171,  -103,   100,    25,
       6,    25,   102,  -103,   205,   146,    97,    97,  -103,    97,
      97,    97,    97,    97,    78,    97,    97,    97,    97,  -103,
    -103,    97,  -103,    97,    30,    97,   183,   113,   194,    65,
      65,    25,    25,    25,   117,   214,   214,   214,   205,  -103,
     131,    45,   194,    97,  -103,    97,    97,    97,    97,  -103,
     119,   194,    17,   194,  -103,    97,   194
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,    10,     0,
       5,     0,     0,     7,     0,     8,     9,     6,    21,     0,
       0,     0,    20,    16,    15,    17,    18,    14,     0,     0,
       0,    21,    11,     0,    22,     0,    19,     0,     0,     0,
      68,     0,     0,     0,     0,     0,    35,    67,     0,    64,
      65,    34,    39,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    36,    66,     0,     0,    24,    37,     0,    50,
       0,    51,     0,    63,    49,     0,    42,     0,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      23,     0,    38,     0,     0,     0,    40,     0,    48,    55,
      56,    57,    58,    59,     0,    52,    53,    54,    60,    25,
      43,     0,    45,    42,    61,    42,     0,     0,     0,    41,
       0,    44,     0,    46,    62,     0,    47
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -103,  -103,  -103,   123,   120,  -103,  -103,  -103,   -28,   104,
    -103,    69,    48,   -33,  -102,  -103,  -103,  -103,  -103,  -103,
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
       1,   119,    74,   120,     8,    75,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     9,    88,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    18,    88,    19,    83,
      84,    14,    93,    76,    98,   125,    99,   100,   101,   102,
     103,    23,   105,   106,   107,   108,     5,    77,    66,    24,
     110,     6,   112,    32,   117,    25,   111,    37,    26,    38,
      67,    12,    27,   118,    33,    39,    20,    81,    82,    83,
      84,    29,    30,   121,   122,   123,    31,    35,    37,    72,
      40,    41,   126,    73,    42,    43,    44,    45,    46,    90,
      37,    47,    38,    48,    49,    50,    92,    51,    39,    94,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   114,
      88,   104,   115,    40,    41,   124,     7,    42,    43,    44,
      45,    46,    17,    89,    47,    36,    48,    49,    50,   109,
      51,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,     0,     0,     0,   116,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     0,    88,     0,    78,    95,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    91,
      88,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    88,   113,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,    88,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,    88,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1
  };

  const signed char
  Parser::yycheck_[] =
  {
      33,    29,     4,     3,    37,    38,    39,    35,    41,    42,
      22,   113,    45,   115,     3,    48,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    25,    20,    10,    11,    12,
      13,    14,    15,    16,    17,    18,     5,    20,     7,    14,
      15,    43,    36,     5,    77,    28,    79,    80,    81,    82,
      83,    21,    85,    86,    87,    88,    42,    19,    91,    29,
      93,     0,    95,     8,    19,    35,    94,     3,    38,     5,
       6,    42,    42,    28,    19,    11,    43,    12,    13,    14,
      15,     7,     6,   116,   117,   118,     9,     7,     3,    43,
      26,    27,   125,    42,    30,    31,    32,    33,    34,     4,
       3,    37,     5,    39,    40,    41,     6,    43,    11,     7,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     6,
      20,    43,     5,    26,    27,     6,     3,    30,    31,    32,
      33,    34,    12,    64,    37,    31,    39,    40,    41,    91,
      43,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    -1,    24,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    20,    -1,     8,    23,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     8,
      20,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    20,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    20,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    20,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    10,    11,    12,    13,    14,    15,
      16,    17,    18
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
      54,    54,    55,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    59,    60,    60,    61,    62,    62,    63,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    68,    68,    69,    69
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     3,     5,     3,     2,     2,
       0,     4,     6,     7,     1,     1,     1,     1,     1,     3,
       1,     0,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     1,
       1,     3,     0,     4,     6,     4,     6,     8,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     6,     2,     1,     1,     1,     1,     1
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
  "booleanLiteral", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   150,   150,   153,   154,   157,   158,   161,   164,   165,
     166,   169,   170,   173,   176,   177,   178,   179,   180,   183,
     184,   185,   188,   191,   194,   195,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     214,   215,   216,   219,   220,   223,   226,   227,   230,   233,
     234,   235,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   249,   250,   253,   256,   257,   258,   261,   262
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
#line 1805 "parser.cpp"

#line 264 "parser.y"


void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    driver.result = 1;
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}
