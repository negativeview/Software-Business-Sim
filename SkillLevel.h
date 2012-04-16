#ifndef SKILL_LEVEL_H
#define SKILL_LEVEL_H

/**
 * A skill level is a class to deal with the funny math when it comes to the
 * differences between what a person thinks of themselves and reality.
 *
 * The believed is what level they believe themselves to be in that skill. This
 * is often, but not always, above the actual skill level. This number is used
 * in things like calculating how much the employee wants to be paid, how they
 * feel about other developers (if MY believed level is about YOUR actual
 * level, I think you are worse than me), and possibly other things.
 *
 * The differences between believed and actual is the primary driver behind a
 * LOT of the uncertainty in this game.
 *
 * The actual skill level is used for how others see you, and how much work
 * you actually get done.
 *
 * This class doesn't keep track of the skill or the entity it is associated
 * with because it's going to be super generic. The most common use is for
 * a Person, but I plan on using these with Companies and how players feel
 * about them, too.
 */

class SkillLevel {
	public:
		SkillLevel(int beleived, int actual);
		~SkillLevel();

		int getBeleived();
		int getActual();
		int getDelusionLevel();
	protected:
		int _believed;
		int _actual;
	private:
};

#endif;