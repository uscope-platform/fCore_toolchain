//
// Created by fils on 24/08/2020.
//

#ifndef FCORE_HAS_ERRORHANDLING_HPP
#define FCORE_HAS_ERRORHANDLING_HPP

#include "antlr4-runtime/ANTLRErrorListener.h"
#include "antlr4-runtime.h"

class ErrorHandling : public  antlr4::ANTLRErrorListener {

    /// <summary>
    /// Upon syntax error, notify any interested parties. This is not how to
    /// recover from errors or compute error messages. <seealso cref="ANTLRErrorStrategy"/>
    /// specifies how to recover from syntax errors and how to compute error
    /// messages. This listener's job is simply to emit a computed message,
    /// though it has enough information to create its own message in many cases.
    /// <p/>
    /// The <seealso cref="RecognitionException"/> is non-null for all syntax errors except
    /// when we discover mismatched token errors that we can recover from
    /// in-line, without returning from the surrounding rule (via the single
    /// token insertion and deletion mechanism).
    /// </summary>
    /// <param name="recognizer">
    ///        What parser got the error. From this
    /// 		  object, you can access the context as well
    /// 		  as the input stream. </param>
    /// <param name="offendingSymbol">
    ///        The offending token in the input token
    /// 		  stream, unless recognizer is a lexer (then it's null). If
    /// 		  no viable alternative error, {@code e} has token at which we
    /// 		  started production for the decision. </param>
    /// <param name="line">
    /// 		  The line number in the input where the error occurred. </param>
    /// <param name="charPositionInLine">
    /// 		  The character position within that line where the error occurred. </param>
    /// <param name="msg">
    /// 		  The message to emit. </param>
    /// <param name="e">
    ///        The exception generated by the parser that led to
    ///        the reporting of an error. It is null in the case where
    ///        the parser was able to recover in line without exiting the
    ///        surrounding rule. </param>
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                             size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;

    /**
     * This method is called by the parser when a full-context prediction
     * results in an ambiguity.
     *
     * <p>Each full-context prediction which does not result in a syntax error
     * will call either {@link #reportContextSensitivity} or
     * {@link #reportAmbiguity}.</p>
     *
     * <p>When {@code ambigAlts} is not null, it contains the set of potentially
     * viable alternatives identified by the prediction algorithm. When
     * {@code ambigAlts} is null, use {@link ATNConfigSet#getAlts} to obtain the
     * represented alternatives from the {@code configs} argument.</p>
     *
     * <p>When {@code exact} is {@code true}, <em>all</em> of the potentially
     * viable alternatives are truly viable, i.e. this is reporting an exact
     * ambiguity. When {@code exact} is {@code false}, <em>at least two</em> of
     * the potentially viable alternatives are viable for the current input, but
     * the prediction algorithm terminated as soon as it determined that at
     * least the <em>minimum</em> potentially viable alternative is truly
     * viable.</p>
     *
     * <p>When the {@link PredictionMode#LL_EXACT_AMBIG_DETECTION} prediction
     * mode is used, the parser is required to identify exact ambiguities so
     * {@code exact} will always be {@code true}.</p>
     *
     * <p>This method is not used by lexers.</p>
     *
     * @param recognizer the parser instance
     * @param dfa the DFA for the current decision
     * @param startIndex the input index where the decision started
     * @param stopIndex the input input where the ambiguity was identified
     * @param exact {@code true} if the ambiguity is exactly known, otherwise
     * {@code false}. This is always {@code true} when
     * {@link PredictionMode#LL_EXACT_AMBIG_DETECTION} is used.
     * @param ambigAlts the potentially ambiguous alternatives, or {@code null}
     * to indicate that the potentially ambiguous alternatives are the complete
     * set of represented alternatives in {@code configs}
     * @param configs the ATN configuration set where the ambiguity was
     * identified
     */
    void reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                                 const antlrcpp::BitSet &ambigAlts, antlr4::atn::ATNConfigSet *configs) override;

    /**
     * This method is called when an SLL conflict occurs and the parser is about
     * to use the full context information to make an LL decision.
     *
     * <p>If one or more configurations in {@code configs} contains a semantic
     * predicate, the predicates are evaluated before this method is called. The
     * subset of alternatives which are still viable after predicates are
     * evaluated is reported in {@code conflictingAlts}.</p>
     *
     * <p>This method is not used by lexers.</p>
     *
     * @param recognizer the parser instance
     * @param dfa the DFA for the current decision
     * @param startIndex the input index where the decision started
     * @param stopIndex the input index where the SLL conflict occurred
     * @param conflictingAlts The specific conflicting alternatives. If this is
     * {@code null}, the conflicting alternatives are all alternatives
     * represented in {@code configs}. At the moment, conflictingAlts is non-null
     * (for the reference implementation, but Sam's optimized version can see this
     * as null).
     * @param configs the ATN configuration set where the SLL conflict was
     * detected
     */
    void reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                             const antlrcpp::BitSet &conflictingAlts, antlr4::atn::ATNConfigSet *configs) override;

    /**
     * This method is called by the parser when a full-context prediction has a
     * unique result.
     *
     * <p>Each full-context prediction which does not result in a syntax error
     * will call either {@link #reportContextSensitivity} or
     * {@link #reportAmbiguity}.</p>
     *
     * <p>For prediction implementations that only evaluate full-context
     * predictions when an SLL conflict is found (including the default
     * {@link ParserATNSimulator} implementation), this method reports cases
     * where SLL conflicts were resolved to unique full-context predictions,
     * i.e. the decision was context-sensitive. This report does not necessarily
     * indicate a problem, and it may appear even in completely unambiguous
     * grammars.</p>
     *
     * <p>{@code configs} may have more than one represented alternative if the
     * full-context prediction algorithm does not evaluate predicates before
     * beginning the full-context prediction. In all cases, the final prediction
     * is passed as the {@code prediction} argument.</p>
     *
     * <p>Note that the definition of "context sensitivity" in this method
     * differs from the concept in {@link DecisionInfo#contextSensitivities}.
     * This method reports all instances where an SLL conflict occurred but LL
     * parsing produced a unique result, whether or not that unique result
     * matches the minimum alternative in the SLL conflicting set.</p>
     *
     * <p>This method is not used by lexers.</p>
     *
     * @param recognizer the parser instance
     * @param dfa the DFA for the current decision
     * @param startIndex the input index where the decision started
     * @param stopIndex the input index where the context sensitivity was
     * finally determined
     * @param prediction the unambiguous result of the full-context prediction
     * @param configs the ATN configuration set where the unambiguous prediction
     * was determined
     */
    void reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                          size_t prediction, antlr4::atn::ATNConfigSet *configs) override;
};



#endif //FCORE_HAS_ERRORHANDLING_HPP
