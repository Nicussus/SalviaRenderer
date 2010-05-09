#include <sasl/include/semantic/semantic_analyser_impl.h>
#include <sasl/include/semantic/symbol.h>
#include <sasl/include/semantic/symbol_infos.h>
#include <sasl/include/syntax_tree/declaration.h>
#include <sasl/include/syntax_tree/program.h>
#include <sasl/include/syntax_tree/statement.h>

BEGIN_NS_SASL_SEMANTIC();

void semantic_analyser_impl::visit( ::sasl::syntax_tree::unary_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::cast_expression& v){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::binary_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::expression_list& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::cond_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::index_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::call_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::member_expression& v ){}

void semantic_analyser_impl::visit( ::sasl::syntax_tree::constant_expression& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::constant& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::identifier& v ){}

// declaration & type specifier
void semantic_analyser_impl::visit( ::sasl::syntax_tree::initializer& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::expression_initializer& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::member_initializer& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::declaration& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::variable_declaration& v ){
	cursym = cursym->add_child( v.name->lit, v.handle() );

	boost::shared_ptr<type_specifier> vartype = v.type_info;
	boost::shared_ptr<type_symbol_info> typesyminfo = extract_symbol_info<type_symbol_info>(vartype);
	
	if ( typesyminfo->type_type() == type_types::buildin ){
		// do buildin
	} else if ( typesyminfo->type_type() == type_types::composited ){
		// do composited
	} else if ( typesyminfo->type_type() == type_types::alias ){
		if ( typesyminfo->full_type() ){
			// do actual
		} else {
			// semantic error: non definition.
		}
	}
}

void semantic_analyser_impl::visit( ::sasl::syntax_tree::type_definition& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::type_specifier& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::buildin_type& v ){

}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::type_identifier& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::qualified_type& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::array_type& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::struct_type& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::parameter& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::function_type& v ){}

// statement
void semantic_analyser_impl::visit( ::sasl::syntax_tree::statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::declaration_statement& v ){
	v.decl->accept(this);
}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::if_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::while_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::dowhile_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::case_label& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::switch_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::compound_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::expression_statement& v ){}
void semantic_analyser_impl::visit( ::sasl::syntax_tree::jump_statement& v ){}

// program
void semantic_analyser_impl::visit( ::sasl::syntax_tree::program& v ){
	is_local = false;
	cursym = symbol::create_root( v.handle() );

	for( size_t i = 0; i < v.decls.size(); ++i){
		v.decls[i]->accept(this);
	}
}

END_NS_SASL_SEMANTIC();